#pragma once
#include "Types.h"
#include "Action.h"
#include "Transform.h"
struct Agent
{
	/// <summary>
	/// ���W
	/// </summary>
	_Point<> position;

	/// <summary>
	/// �G�[�W�F���g�𓮂���
	/// </summary>
	/// <param name="dir">����������</param>
	void Move(Direction dir)
	{
		position += Transform::DirToDelta(dir);
	}
};

