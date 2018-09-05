#include "Drawer.h"
#include "LogicUtil.h"
#include "StatusDrawer.h"
void Drawer::DrawField(const Field & field) const
{
	// �Z���ƃ^�C���|�C���g�̕`��
	Rect r;
	
	auto cells = field.GetCells();
	
	for (int i = 0; i < cells.size().x; i++)
	{
		for (int k = 0; k < cells.size().y; k++)
		{
			Point pos(i, k);
			Point top_left_pos = fieldOrigin + pos * cellSize;
			
			r = Rect(top_left_pos, cellSize);

			r.draw(Palette::White);

			if (cells[k][i].GetTile() != TileType::None)
			{
				r.draw(Color(TeamColor::ColorOf(cells[k][i].GetTile()), 50U));
			}
			
			r.drawFrame(1.0, Palette::Gray);
			
			FontAsset(U"Cell")(cells[k][i].GetPoint())
				.drawAt(r.center(), Palette::Black);
		}
	}
}

void Drawer::DrawAgents(HashTable<TeamType, Array<Agent>> agents) const
{
	int32 edge_width = Sqrt(2) * cellSize.x / 2.0;

	auto center = [=](Point pos) {return fieldOrigin + pos * cellSize + cellSize / 2; };
	for(TeamType team : {TeamType::A, TeamType::B})
	{
		// ��l�ڂ̃G�[�W�F���g��`��
		Circle(center(LogicUtil::toS3dPoint(agents[team][0].GetPosition())), cellSize.x / 2)
			.drawFrame(2.0, TeamColor::ColorOf(team));

		// ��l�ڂ̃G�[�W�F���g��`��
		Rect(Arg::center = center(LogicUtil::toS3dPoint(agents[team][1].GetPosition())), edge_width).rotated(45_deg)
			.drawFrame(2.0, TeamColor::ColorOf(team));
	}
}

void Drawer::DrawStatus(const HashTable<TeamType, Think> & thinks, const Field & field, int turn) const
{
	if (thinks.size() == 0)
	{
		return;
	}

	Array<Array<String>> messages{ 3 };

	// 2�`�[���̏��
	for (int i : step(2))
	{
		messages[i].append
		({
			String(U"Agent 1 : ") + Transform::ToString(thinks.at((TeamType)i).steps[0]),
			String(U"Agent 2 : ") + Transform::ToString(thinks.at((TeamType)i).steps[1]),
			String(U"Area Point : ") + ToString(field.GetAreaPoints()[i]),
			String(U"Tile Point : ") + ToString(field.GetTilePoints()[i]),
			String(U"Total Point : ") + ToString(field.GetTotalPoints()[i])
		});
	}

	// ���̑��̃Q�[�����
	messages[2].push_back(String(U"Turn : ") + ToString(turn));

	// �X�e�[�^�X��`��
	StatusDrawer status_drawer{ statOrigin };
	// �e�`�[���̏���`��
	for (int i : step(2))
	{
		auto team_color = TeamColor::ColorOf((TeamType)i);
		// �`�[������`��
		auto text = FontAsset(U"Stat")(Transform::ToString((TeamType)i));
		status_drawer.DrawStatus(text, team_color);
		
		// �`��ʒu�����s
		
		for (size_t k : step(messages[i].count()))
		{
			text = FontAsset(U"Stat")(messages[i][k]);
			status_drawer.DrawStatus(text, team_color);
		}
	}

	for (size_t i : step(messages[2].count()))
	{
		status_drawer.DrawStatus(FontAsset(U"Stat")(messages[2][i]));
	}
}

Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}
