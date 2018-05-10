#include "GameLogic.h"
HashTable<TeamType, Array<Agent>> GameLogic::GetAgentMap() const
{
	HashTable<TeamType, Array<Agent>> agents;
	agents[TeamType::A] = _teamlogics[0].GetAgents();
	agents[TeamType::B] = _teamlogics[1].GetAgents();

	return agents;
}
Array<Agent> GameLogic::GetAgents() const
{
	return _teamlogics[0].GetAgents().append(_teamlogics[1].GetAgents());
}
Array<TeamLogic>& GameLogic::getTeamLogics()
{
	return _teamlogics;
}
void GameLogic::initAgentsPos()
{
	Size size = _field.GetCells().size();

	initAgentsPos(Point(Random((size.x - 2) / 2), Random((size.y - 2) / 2)));
}

void GameLogic::initAgentsPos(Point init_pos)
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

	_teamlogics[0].InitAgentsPos(agent_pos[0], agent_pos[1]);
	_teamlogics[1].InitAgentsPos(agent_pos[2], agent_pos[3]);
}


void GameLogic::InitalizeFromJson(const String path)
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


int GameLogic::GetTurn() const
{
	return _turn;
}

void GameLogic::NextTurn(HashTable<TeamType, Think> &_thinks)
{
	if (_turn <= 0)
	{
		return;
	}
	auto agents_map = GetAgentMap();
	auto agents = GetAgents();

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
			_teamlogics[static_cast<int>(team)].MoveAgent(pos, dir);
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

Field GameLogic::GetField() const
{
	return _field;
}

GameLogic::GameLogic() :_teamlogics({ TeamLogic(),TeamLogic() })
{

}

GameLogic::~GameLogic()
{
}
