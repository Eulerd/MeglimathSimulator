#include "FieldDrawer.h"

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

	Point pos, top_left_pos, center_pos;
	int32 edge_width = Sqrt(2) * cellSize.x / 2.0;

	auto center = [=](Point pos) {return fieldOrigin + pos * cellSize + cellSize / 2; };
	for(TeamType team : {TeamType::A, TeamType::B})
	{
		// ��l�ڂ̃G�[�W�F���g��`��
		Circle(center(agents[team][0].GetPosition()), cellSize / 2).draw(color_map[team]);

		// ��l�ڂ̃G�[�W�F���g��`��
		Rect(Arg::center = center(agents[team][1].GetPosition()), edge_width).rotated(45_deg)
			.draw(color_map[team]);
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
