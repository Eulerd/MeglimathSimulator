#include "KeyBoardTeam.h"



Optional<Direction> KeyBoardTeam::DecideDirectionByKey()
{
	Optional<Direction> dir = none;

	// Right���甽���v���
	Array<Key> keys = { KeyD, KeyE, KeyW, KeyQ, KeyA, KeyZ, KeyX, KeyC, KeyS };

	for (int i : step(9))
	{
		if (keys[i].down())
		{
			return Optional<Direction>(static_cast<Direction>(i));
		}
	}
	
	return dir;
}

void KeyBoardTeam::Update(const Field & field)
{
	if (_next_steps[0].has_value() && _next_steps[1].has_value())
	{
		return;
	}

	int index = (_next_steps[0].has_value() ? 1 : 0);

	Optional<Direction> next_dir = DecideDirectionByKey();

	if (!next_dir.has_value())
	{
		return;
	}

	// ��l�ڂ̃G�[�W�F���g�̍s�������܂����珀������
	if (index == 1)
	{
		_is_ready = true;
	}

	// �G�[�W�F���g�̍��W����w��̕����ɐi�񂾍��W
	Point next_pos = _agents[index].GetPosition().moveBy(Transform::DirToDelta(next_dir.value()));

	if (next_dir.value() == Direction::Stop)
	{
		_next_steps[index] = Step{ Action::Stop, next_dir.value() };
		return;
	}

	// �i�񂾐�̃^�C���̗L���ŃA�N�V���������߂�
	if (field.GetCells()[next_pos.y][next_pos.x].GetTile() == TileType::None)
	{
		_next_steps[index] = Step{ Action::Move, next_dir.value() };
	}
	else
	{
		_next_steps[index] = Step{ Action::RemoveTile, next_dir.value() };
	}

}

KeyBoardTeam::KeyBoardTeam(TeamType type)
	: Team(type, Agent(), Agent())
{
	_is_ready = false;
}

KeyBoardTeam::KeyBoardTeam(TeamType type, Agent agent1, Agent agent2)
	: Team(type, agent1, agent2)
{
	_is_ready = false;
}

KeyBoardTeam::~KeyBoardTeam()
{
}
