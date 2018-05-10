#pragma once

/// <summary>
/// �G�[�W�F���g�̓���
/// </summary>
enum class Action
{
	Move, RemoveTile, Stop
};

/// <summary>
/// ����̕���
/// </summary>
enum class Direction
{
	Right,
	RightUp,
	Up,
	LeftUp,
	Left,
	LeftDown,
	Down,
	RightDown,
	Stop
};

struct Step
{
	Action action;
	Direction direction;
};