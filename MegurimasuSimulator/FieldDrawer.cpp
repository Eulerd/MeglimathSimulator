#include "FieldDrawer.h"


void FieldDrawer::SetOrigin(Point origin) 
{
	_origin = origin;
}

Point FieldDrawer::GetOrigin() const
{
	return _origin;
}

void FieldDrawer::Draw(const GameInfo & info) const
{

	// �Z���ƃ^�C���|�C���g�̕`��
	Rect r;
	auto cells = info.GetField().GetCells();
	Array<Agent> a_agents = info.GetAgents(TeamType::A);
	Array<Agent> b_agents = info.GetAgents(TeamType::B);
	
	for (int i = 0; i < cells.size().x; i++)
	{
		for (int k = 0; k < cells.size().y; k++)
		{
			Point pos(i, k);
			Point top_left_pos = _origin + pos * _c_size;
			Point center_pos = top_left_pos + _c_size / 2;
			int32 edge_width = Sqrt(2) * _c_size.x / 2.0;

			r = Rect(top_left_pos, _c_size);

			r.draw(Transform::ColorOf(cells[k][i].GetTile()));

			// �G�[�W�F���g������ꍇ�g�̐F��ς���
			auto pos_lamda = [pos](const Agent & agent) {return agent.GetPosition() == pos; };

			r.drawFrame(1.0, Palette::Gray);

			// �`�[��A�̃G�[�W�F���g��`��
			if (pos == a_agents[0].GetPosition())
			{
				Circle(center_pos, _c_size.x / 2).draw(Palette::Red);
			}
			if (pos == a_agents[1].GetPosition())
			{
				// �Ђ��`
				Rect(Arg::center = center_pos, edge_width).rotated(45_deg)
					.draw(Palette::Red);
			}

			// �`�[��B�̃G�[�W�F���g��`��
			if (pos == b_agents[0].GetPosition())
			{
				Circle(center_pos, _c_size.x / 2).draw(Palette::Blue);
			}
			if (pos == b_agents[1].GetPosition())
			{
				// �Ђ��`
				Rect(Arg::center = center_pos, edge_width).rotated(45_deg)
					.draw(Palette::Blue);
			}

			FontAsset(U"Cell")(cells[k][i].GetPoint()).drawAt(r.center(), Palette::Black);
		}
	}


}

FieldDrawer::FieldDrawer()
{
}


FieldDrawer::~FieldDrawer()
{
}

void FieldDrawer::operator=(const FieldDrawer & other)
{
	_origin = other._origin;
}
