#pragma once
#include <Siv3D.hpp>
#include "Types.h"
#include "Action.h"

namespace Transform
{
	/// <summary>
	/// ��������ړ������ɕϊ�����
	/// </summary>
	/// <param name="dir">�ϊ����̕���</param>
	/// <returns>������ϊ������ړ�����</returns>
	constexpr Point DirToDelta(Direction dir)
	{
		switch (dir)
		{
		case Direction::Right:
			return Point(1, 0);
			
		case Direction::RightUp:
			return Point(1, -1);
			
		case Direction::Up:
			return Point(0, -1);
			
		case Direction::LeftUp:
			return Point(-1, -1);
			
		case Direction::Left:
			return Point(-1, 0);

		case Direction::LeftDown:
			return Point(-1, 1);
			
		case Direction::Down:
			return Point(0, 1);
			
		case Direction::RightDown:
			return Point(1, 1);
			
		}
		return Point(0, 0);
	}

	const String ToString(Action action);

	const String ToString(Direction dir);

	const String ToString(Step step);

	const String ToString(TeamType team);

	const char ToChar(TileType tile);
}