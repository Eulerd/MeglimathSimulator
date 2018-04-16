#include "Drawer.h"

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

			r.draw(Transform::ColorOf(cells[k][i].GetTile()));

			// �G�[�W�F���g������ꍇ�g�̐F��ς���
			auto pos_lamda = [pos](const Agent & agent) {return agent.GetPosition() == pos; };

			r.drawFrame(1.0, Palette::Gray);

			FontAsset(U"Cell")(cells[k][i].GetPoint()).drawAt(r.center(), Palette::Black);
		}
	}
}

void Drawer::DrawAgents(std::map<TeamType, Array<Agent>> agents) const
{
	// �`�[��A�̃G�[�W�F���g��`��
	std::map<TeamType, Color> color_map;
	color_map[TeamType::A] = Palette::Red;
	color_map[TeamType::B] = Palette::Blue;

	Point pos;
	int32 edge_width = Sqrt(2) * cellSize.x / 2.0;

	auto center = [=](Point pos) {return fieldOrigin + pos * cellSize + cellSize / 2; };
	for(TeamType team : {TeamType::A, TeamType::B})
	{
		// ��l�ڂ̃G�[�W�F���g��`��
		Circle(center(agents[team][0].GetPosition()), cellSize.x / 2).drawFrame(2.0, color_map[team]);

		// ��l�ڂ̃G�[�W�F���g��`��
		Rect(Arg::center = center(agents[team][1].GetPosition()), edge_width).rotated(45_deg)
			.drawFrame(2.0, color_map[team]);
	}
}

void Drawer::DrawStat(const std::map<TeamType, Think> & thinks, int turn) const
{
	if (thinks.size() == 0)
	{
		return;
	}
	
	Array<String> messages =
	{
		U"Team A : ",
		String(U"Agent 1 : ") + Transform::ToString(thinks.at(TeamType::A).steps[0]),
		String(U"Agent 2 : ") + Transform::ToString(thinks.at(TeamType::A).steps[1]),
		String(U"\n"),
		U"Team B : ",
		String(U"Agent 1 : ") + Transform::ToString(thinks.at(TeamType::B).steps[0]),
		String(U"Agent 2 : ") + Transform::ToString(thinks.at(TeamType::B).steps[1]),
		String(U"\n"),
		String(U"Turn : ") + ToString(turn)
	};

	for (int i : step(messages.size()))
	{
		FontAsset(U"Stat")(messages[i]).draw(statOrigin + Point(0, i * 16));
	}
}

Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}

void Drawer::operator=(const Drawer & other)
{}
