#pragma once
#include "Action.h"
#include<array>
#include <rapidjson\document.h>
#include <string>

/// <summary>
/// �G�[�W�F���g��l���̍s��
/// </summary>
struct Think
{
	std::array<Step,2> steps;

	static Think makeThink(std::string json);
};