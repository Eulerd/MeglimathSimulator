#include "Game.h"

bool Game::dfsAreaPoint(Point pos, TileType tile)
{
	auto cells = _field.GetCells();

	if (cells[pos.y][pos.x].GetTile() == tile)
	{
		return true;
	}

	_arrives.push_back(pos);

	Point delta[] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

	Point next_pos;
	// �l���Ń^�C���̂Ȃ��}�X���������炻�̃}�X�֒T��
	for (int i : step(4))
	{
		next_pos = pos + delta[i];

		// �t�B�[���h�O
		if (next_pos.x < 0 || next_pos.y < 0 || next_pos.x >= cells.width() || next_pos.y >= cells.height())
		{
			return false;
		}

		// �T���ς݂Ȃ�T�����Ȃ�
		if (_arrives.includes(next_pos))
		{
			continue;
		}

		auto next_tile = cells[next_pos.y][next_pos.x].GetTile();

		if(next_tile == TileType::None)
		{
			// ��̃}�X���͂܂�Ă��Ȃ��ꍇ���̃}�X���͂܂�Ă��Ȃ�
			if (!dfsAreaPoint(next_pos, tile))
			{
				return false;
			}
		}
		else if (next_tile != tile)
		{
			return false;
		}
	}

	return true;
}

GameInfo Game::getGameInfo() const
{
	return GameInfo(_field, getAgentMap());
}

std::map<TeamType, Array<Agent>> Game::getAgentMap() const
{
	std::map<TeamType, Array<Agent>> agents;
	agents[TeamType::A] = _teams[0]->GetAgents();
	agents[TeamType::B] = _teams[1]->GetAgents();

	return agents;
}

Array<Agent> Game::getAgents() const
{
	return _teams[0]->GetAgents().append(_teams[1]->GetAgents());
}

void Game::InitAgents()
{
	Size size = _field.GetCells().size();

	Point init_pos = Point(Random((size.x - 2) / 2), Random((size.y - 2) / 2));

	size -= Point(1, 1);
	Point agent_pos[] = 
	{
		init_pos,
		Point(size.x - init_pos.x, init_pos.y),
		Point(init_pos.x, size.y - init_pos.y),
		size - init_pos
	};

	_teams[0]->InitAgentsPos(agent_pos[0], agent_pos[1]);
	_teams[1]->InitAgentsPos(agent_pos[2], agent_pos[3]);
}

void Game::Update()
{
	std::map<TeamType, Think> thinks;
	
	GameInfo info = getGameInfo();
	auto agents_map = getAgentMap();
	auto agents = getAgents();

	thinks[TeamType::A] = _teams[0]->NextThink(info);
	thinks[TeamType::B] = _teams[1]->NextThink(info);

	// �V�~�����[�V����
	Array<std::pair<Point, std::pair<Direction, TeamType>>> move_point_arr;
	Array<Point> remove_points;
	for (TeamType team : {TeamType::A, TeamType::B})
	{
		for (int i = 0; i < 2; i++)
		{
			Direction dir = thinks[team].agents[i].direction;
			// �G�[�W�F���g�𓮂������������ɓ��������ꍇ�̍��W
			Point pos = agents_map[team][i].GetPosition().movedBy(Transform::DirToDelta(dir));

			// �G�[�W�F���g�����삷����W��ǉ�
			switch (thinks[team].agents[i].action)
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

			// ���̍��W�ɖ߂�
			pos -= Transform::DirToDelta(dir);

			_teams[static_cast<int>(team)]->MoveAgent(pos, dir);
			_field.PaintCell(pos, team);
		}
	}

	for (auto & remove_point : remove_points)
	{
		if (remove_points.count_if(Equal(remove_point)) == 1 && _field.IsInField(remove_point))
		{
			_field.RemoveTile(remove_point);
		}
	}
	
}

void Game::Draw() const
{
	_field_drawer.Draw(getGameInfo());
}

Game::Game(const Field & field, std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b)
{
	_field = field;
	_teams.append({ team_a, team_b });
}

Game::~Game()
{
}
