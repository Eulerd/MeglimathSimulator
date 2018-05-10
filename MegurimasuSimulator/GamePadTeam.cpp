#include "GamePadTeam.h"



Optional<Direction> GamePadTeam::decideDirectionByGamePad()
{
	Optional<Direction> dir = none;

	if (!Gamepad(0).isConnected())
	{
		return dir;
	}

	// B�{�^���������ꂽ��Stop
	if (Gamepad(0).buttons[1].down())
	{
		return Direction::Stop;
	}

	// A�{�^���������Č���
	if (!Gamepad(0).buttons[0].down())
	{
		return none;
	}

	// �\���L�[�̕���
	Point d_pad = Point((int)Gamepad(0).axes[0], (int)Gamepad(0).axes[1]);

	// �E���甽���v���̃L�[�̕������X�g
	Array<Point> dir_delta = { {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1} };

	double threshold = 0.1;

	for (size_t i : step(dir_delta.count()))
	{
		Point delta = dir_delta[i];
		if (delta.x - threshold < d_pad.x && d_pad.x <= delta.x
			&& delta.y - threshold < d_pad.y && d_pad.y <= dir_delta[i].y)
		{
			return (Direction)i;
		}
	}
	
	return dir;
}

void GamePadTeam::Update(const Field & field)
{
	// ���łɍs�������肵�Ă����ꍇ�I��
	if (_next_steps[0].has_value() && _next_steps[1].has_value())
	{
		return;
	}

	// ���ɂǂ���̍s�������肷��̂���ݒ�
	int index = (_next_steps[0].has_value() ? 1 : 0);

	Optional<Direction> next_dir = decideDirectionByGamePad();

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

GamePadTeam::GamePadTeam(TeamLogic &team)
	:WaitingForInputTeam(team) {}


GamePadTeam::~GamePadTeam()
{
}
