#include "KeyBoardTeam.h"



Optional<Direction> KeyBoardTeam::decideDirectionByKey()
{
	Optional<Direction> dir = none;

	// Right���甽���v���ɕ����L�[���w��
	for (int i : step(9))
	{
		if (_operation_keys[i].down())
		{
			return Optional<Direction>(static_cast<Direction>(i));
		}
	}
	
	return dir;
}

void KeyBoardTeam::Update(const Field & field)
{
	// ���łɍs�������肵�Ă����ꍇ�I��
	if (_next_steps[0].has_value() && _next_steps[1].has_value())
	{
		return;
	}

	// ���ɂǂ���̍s�������肷��̂���ݒ�
	int index = (_next_steps[0].has_value() ? 1 : 0);

	Optional<Direction> next_dir = decideDirectionByKey();

	if (!next_dir.has_value())
	{
		return;
	}

	// ��l�ڂ̃G�[�W�F���g�̍s�������܂����珀������
	if (index == 1)
	{
		_is_ready = true;
	}

	_next_steps[index] =
		field.DecideStepByDirection(_team.GetAgents()[index].GetPosition(), next_dir.value());
}

KeyBoardTeam::KeyBoardTeam(TeamLogic &team, Array<Key> operation_keys)
	: WaitingForInputTeam(team)
{
	_operation_keys = operation_keys;
	_is_ready = false;
}

KeyBoardTeam::~KeyBoardTeam()
{
}
