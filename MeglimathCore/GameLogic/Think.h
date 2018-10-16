#pragma once
#include<array>
#include <rapidjson\document.h>
#include <string>

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

/// <summary>
/// �G�[�W�F���g��l���̍s��
/// </summary>
struct Think
{
	std::array<Step,2> steps;

	static Think makeThink(std::string json);
};