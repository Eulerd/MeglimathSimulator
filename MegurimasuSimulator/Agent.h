#pragma once
#include <Siv3D.hpp>
#include "Action.h"

class Agent
{
private:
	/// <summary>
	/// �擾�����^�C���|�C���g
	/// </summary>
	int _tile_point;

	/// <summary>
	/// ���W
	/// </summary>
	Point _position;

	Actions _actions;

public:
	Agent();
	virtual ~Agent();
};

