#include "Game.h"

GameInfo Game::getGameInfo() const
{
	return GameInfo(_field, GetAgentMap());
}

HashTable<TeamType, Array<Agent>> Game::GetAgentMap() const
{
	HashTable<TeamType, Array<Agent>> agents;
	agents[TeamType::A] = _teams[0]->GetAgents();
	agents[TeamType::B] = _teams[1]->GetAgents();

	return agents;
}

Array<Agent> Game::GetAgents() const
{
	return _teams[0]->GetAgents().append(_teams[1]->GetAgents());
}

void Game::initAgentsPos()
{
	Size size = _field.GetCells().size();

	initAgentsPos(Point(Random((size.x - 2) / 2), Random((size.y - 2) / 2)));
}

void Game::initAgentsPos(Point init_pos)
{
	Size size = _field.GetCells().size();

	size -= Point(1, 1);
	Point agent_pos[] =
	{
		init_pos,
		Point(size.x - init_pos.x, init_pos.y),
		Point(init_pos.x, size.y - init_pos.y),
		size - init_pos
	};

	// �G�[�W�F���g�̏����ʒu�̃^�C����h��
	_field.PaintCell(agent_pos[0], TeamType::A);
	_field.PaintCell(agent_pos[1], TeamType::A);

	_field.PaintCell(agent_pos[2], TeamType::B);
	_field.PaintCell(agent_pos[3], TeamType::B);

	_teams[0]->InitAgentsPos(agent_pos[0], agent_pos[1]);
	_teams[1]->InitAgentsPos(agent_pos[2], agent_pos[3]);
}

void Game::InitalizeFromJson(const String path)
{
	JSONReader json(path);

	_field = Field(path);

	if (json[U"InitPos"].isNull())
	{
		initAgentsPos();
	}
	else
	{
		initAgentsPos(json[U"InitPos"].get<Point>());
	}

	_turn = json[U"Turn"].get<int>();
}

bool Game::IsReady()
{
	return _teams[0]->IsReady() && _teams[1]->IsReady();
}

int Game::GetTurn() const
{
	return _turn;
}

void Game::NextTurn()
{
	if (_turn <= 0)
	{
		return;
	}
	
	GameInfo info = getGameInfo();
	auto agents_map = GetAgentMap();
	auto agents = GetAgents();

	_thinks[TeamType::A] = Think(_teams[0]->NextThink(info));
	_thinks[TeamType::B] = Think(_teams[1]->NextThink(info));

	// �V�~�����[�V����
	Array<std::pair<Point, std::pair<Direction, TeamType>>> move_point_arr;
	Array<Point> remove_points;
	for (TeamType team : {TeamType::A, TeamType::B})
	{
		for (int i = 0; i < 2; i++)
		{
			Direction dir = _thinks[team].steps[i].direction;
			// �G�[�W�F���g�𓮂������������ɓ��������ꍇ�̍��W
			Point pos = agents_map[team][i].GetPosition().movedBy(Transform::DirToDelta(dir));

			// �G�[�W�F���g�����삷����W��ǉ�
			switch (_thinks[team].steps[i].action)
			{
			case Action::Move:
				move_point_arr.push_back(std::make_pair(pos, std::make_pair(dir, team)));
				break;
			case Action::RemoveTile:
				remove_points.push_back(pos);
				break;
			}
		}
	}

	// �Փ˂��Ă��Ȃ��G�[�W�F���g�̍s���̂ݎ��s����
	for (auto & pos_map : move_point_arr)
	{
		auto pos = pos_map.first;

		// ���̍��W�ɍs���G�[�W�F���g����l�A�t�B�[���h��
		// �^�C�����u����Ă��Ȃ��A�ǂ̃G�[�W�F���g�����Ȃ�
		if (move_point_arr.count_if([pos](std::pair<Point, std::pair<Direction, TeamType>> itr) {return itr.first == pos; }) == 1
			&& _field.IsInField(pos)
			&& _field.GetCells()[pos.y][pos.x].GetTile() == TileType::None
			&& agents.count_if([pos](Agent agent) { return agent.GetPosition() == pos; }) == 0)
		{
			auto dir = pos_map.second.first;
			auto team = pos_map.second.second;

			// �i�񂾃Z����h��
			_field.PaintCell(pos, team);

			// ���̍��W�ɖ߂�
			pos -= Transform::DirToDelta(dir);

			// �G�[�W�F���g�𓮂���
			_teams[static_cast<int>(team)]->MoveAgent(pos, dir);
		}
	}

	// �^�C�������s�������s
	for (auto & remove_point : remove_points)
	{
		if (remove_points.count_if(Equal(remove_point)) == 1 && _field.IsInField(remove_point))
		{
			_field.RemoveTile(remove_point);
		}
	}
	
	// �^�[����i�߂�
	_turn--;

	// �`�[���̓��_���X�V
	_field.UpdatePoint();
}

void Game::Update()
{
	_teams[0]->Update(_field);
	_teams[1]->Update(_field);
}

Field Game::GetField() const
{
	return _field;
}

HashTable<TeamType, Think> Game::GetThinks() const
{
	return _thinks;
}

Game::Game(std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b)
{
	_teams.append({ team_a, team_b });
}

Game::~Game()
{
}
