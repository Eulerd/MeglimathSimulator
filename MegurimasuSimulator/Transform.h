#pragma once
#include <Siv3D.hpp>
#include "TeamType.h"
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

	/// <summary>
	/// �^�C���̎�ނ���F���擾����
	/// </summary>
	/// <param name="t_type">�^�C���̎��</param>
	/// <returns>�^�C���̐F</returns>
	constexpr Color ColorOf(TileType t_type)
	{
		switch (t_type)
		{
		case TileType::A:
			return Palette::Red;
		case TileType::B:
			return Palette::Blue;
		case TileType::None:
		default:
			return Palette::White;
		}
	}

	const String ToString(Action action);

	const String ToString(Direction dir);

	const String ToString(Step step);
}