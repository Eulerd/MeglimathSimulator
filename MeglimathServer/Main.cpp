﻿
# include <Siv3D.hpp> // OpenSiv3D v0.2.5
#include <HamFramework.hpp>

#include <rapidjson\document.h>
#include <rapidjson\writer.h>

#include "../MeglimathCore/Game.h"
#include "../MeglimathCore/Drawer.h"
#include "../MeglimathCore/TCPString.hpp"
#include "../MeglimathCore/CreateJson.h"

#include <Windows.h>

struct GameData
{
	Game game;
	Drawer drawer;
	std::map<SessionID, TeamType> team_table;
	std::map<TeamType, Optional<Think>> thinks;
	asc::TCPStringServer server;

	int command_id = -1;
};

using MyApp = SceneManager<String, GameData>;

namespace Scenes
{
	class ReadFieldJson : public MyApp::Scene
	{
	public:
		ReadFieldJson(const InitData& init) : IScene(init)
		{
			// フィールド情報を受け取るための通信
			getData().server.startAccept(31401);
		}

		void update() override
		{
			auto & server = getData().server;

			if (server.hasSession())
			{
				// フィールド情報を受信
				String field_json;
				server.readLine(field_json);
				field_json.remove(U"\n");

				if (field_json != U"")
				{
					// ゲームの初期化
					getData().game = { field_json };

					if (getData().command_id == 0)
					{
						getData().game.SpinLeft90();
					}
					else if(getData().command_id == 1)
					{
						getData().game.SpinRight90();
					}

					// クライアントとの接続へ移行
					server.sendString(U"ok\n", server.getSessionIDs()[0]);

					changeScene(U"Connection", 0);
					return;
				}
			}
		}

		void draw() const override
		{
			FontAsset(U"Msg")(U"フィールド情報受信中...").draw(Point::Zero());
		}
	};


	class Connection : public MyApp::Scene
	{
	public:
		Connection(const InitData& init) : IScene(init)
		{
			// 初期化
			getData().team_table.clear();
			getData().server.cancelAccept();
			getData().server.disconnect();

			// 二つのクライアントと接続する
			getData().server.startAcceptMulti(31400);
		}

		void update() override
		{
			if (getData().server.num_sessions() == 2)
			{
				changeScene(U"HandShake", 0);
			}

		}

		void draw() const override
		{
			getData().drawer.DrawField(getData().game.GetField());
			FontAsset(U"Msg")(U"待機中... 接続数 : ", getData().server.num_sessions()).draw(Point(0, 0));
		}
	};

	class HandShake : public MyApp::Scene
	{
	public:
		HandShake(const InitData& init) : IScene(init)
		{
		}

		void update() override
		{
			auto & server = getData().server;

			if (server.num_sessions() != 2)
			{
				server.disconnect();
				server.cancelAccept();

				changeScene(U"Connection", 0);
			}

			for (auto i = 0; i < server.num_sessions(); i++)
			{
				auto ids = server.getSessionIDs();

				String json_dat;
				server.readUntil(U'\n', json_dat, ids[i]);
				json_dat.remove(U'\n');

				if (json_dat.isEmpty())	
				{
					continue;
				}

				TeamType type;
				if (json_dat == U"Red") type = TeamType::Red;
				else if (json_dat == U"Blue") type = TeamType::Blue;
				else return;

				if (getData().team_table.empty()
					|| getData().team_table[ids[1 - i]] != type)
				{
					getData().team_table[ids[i]] = type;

					server.sendString(U"OK\n", ids[i]);
				}
				else
				{
					// チーム種類が重複している
					server.sendString(U"Type\n", ids[i]);
				}
			}

			if (getData().team_table.size() == 2)
			{
				changeScene(U"Game", 0);
				return;
			}
		}

		void draw() const override
		{
			FontAsset(U"Msg")(U"パラメータ設定中...").draw(Point(0, 0));
		}
	};

	class Game : public MyApp::Scene
	{
	private:
		void sendGameInfo()
		{
			auto str = Unicode::Widen(Transform::CreateJson(getData().game.GetGameInfo()));
			str.push_back('\n');

			for (auto id : getData().server.getSessionIDs())
			{
				getData().server.sendString(str, id);
			}
		}

	public:
		Game(const InitData& init) : IScene(init)
		{
			sendGameInfo();

			getData().thinks[TeamType::Red] = none;
			getData().thinks[TeamType::Blue] = none;
		}

		void update() override
		{
			auto & data = getData();
			if (data.server.num_sessions() != 2)
			{
				data.server.disconnect();
				data.server.cancelAccept();

				changeScene(U"Connection", 0);
			}

			// Clientから次ターンの行動を受け取る
			for (auto id : data.server.getSessionIDs())
			{
				String json_dat;
				data.server.readUntil('\n', json_dat, Optional<SessionID>(id));

				if (json_dat.isEmpty())
				{
					continue;
				}

				// jsonからThink情報を取得
				rapidjson::Document doc;
				doc.Parse(json_dat.narrow().data());

				data.thinks[data.team_table[id]] = Think::makeThink(json_dat.narrow());
			}

			// Client二つ分のThinkが更新されたら次のターンへ
			auto ids = data.server.getSessionIDs();
			auto table = data.team_table;

			if (ids.size() != 2)
			{
				return;
			}

			auto &thinks = data.thinks;
			if (thinks[TeamType::Red].has_value() && thinks[TeamType::Blue].has_value())
			{
				getData().game.NextTurn(thinks[TeamType::Blue].value(), thinks[TeamType::Red].value());

				// Think情報を初期化
				thinks[TeamType::Red] = none;
				thinks[TeamType::Blue] = none;

				sendGameInfo();
			}

			if (KeyLeft.down())
			{
				data.game.Undo();
				sendGameInfo();
			}

			if (KeyRight.down())
			{
				data.game.Redo();
				sendGameInfo();
			}
		}

		void draw() const override
		{
			auto & game = getData().game;
			auto & drawer = getData().drawer;
			auto field = game.GetField();

			drawer.DrawField(field);
			drawer.DrawAgents(game.GetAgentMap());
			drawer.DrawStatus(game.GetThinks(), field, game.GetTurn());
		}
	};
}

void Main()
{
	Window::SetPos(850, 0);

	MyApp manager;
	manager
		.add<Scenes::ReadFieldJson>(U"ReadFieldJson")
		.add<Scenes::Connection>(U"Connection")
		.add<Scenes::Game>(U"Game")
		.add<Scenes::HandShake>(U"HandShake");
	
	const auto p = manager.get();

	// コマンドライン引数
	int nArgs = 0;
	LPWSTR* szArglist = ::CommandLineToArgvW(::GetCommandLineW(), &nArgs);

	if (nArgs >= 2)
	{
		String arg = Unicode::FromWString(szArglist[1]);
		int command_id = Parse<int>(arg);

		p->command_id = command_id;
	}

	FontAsset::Register(U"Msg", 32);
	FontAsset::Register(U"Cell", 16, Typeface::Black);
	FontAsset::Register(U"Stat", 16, Typeface::Default);

	Window::SetTitle(U"TCP Server");

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}
