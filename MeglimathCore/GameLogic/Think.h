#pragma once
#include "Action.h"
#include <rapidjson\document.h>
#include <string>

/// <summary>
/// �G�[�W�F���g��l���̍s��
/// </summary>
class Think
{
public:
	Step steps[2];

	Think(std::string json);
	Think(Step steps[2]);
	Think(Step step1, Step step2);
	Think();
	~Think();
};