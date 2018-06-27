#pragma once
#include "Types.h"
#include "Action.h"


namespace Transform
{
	
	/// <summary>
	/// ��������ړ������ɕϊ�����
	/// </summary>
	/// <param name="dir">�ϊ����̕���</param>
	/// <returns>������ϊ������ړ�����</returns>
	constexpr _Point<int> DirToDelta(Direction dir)
	{
		switch (dir)
		{
		case Direction::Right:
			return _Point<int>(1, 0);
			
		case Direction::RightUp:
			return _Point<int>(1, -1);
			
		case Direction::Up:
			return _Point<int>(0, -1);
			
		case Direction::LeftUp:
			return _Point<int>(-1, -1);
			
		case Direction::Left:
			return _Point<int>(-1, 0);

		case Direction::LeftDown:
			return _Point<int>(-1, 1);
			
		case Direction::Down:
			return _Point<int>(0, 1);
			
		case Direction::RightDown:
			return _Point<int>(1, 1);
			
		}
		return _Point<int>(0, 0);
	}

	constexpr TileType ToTile(TeamType team)
	{
		switch (team)
		{
		case TeamType::A:
			return TileType::A;

		case TeamType::B:
			return TileType::B;
		}

		return TileType::None;
	}

	constexpr TileType GetInverseType(TileType tile)
	{
		switch (tile)
		{
		case TileType::A:
			return TileType::B;
		case TileType::B:
			return TileType::A;
		}

		return TileType::None;
	}

	const std::u32string ToString(Action action);

	const std::u32string ToString(Direction dir);

	const std::u32string ToString(Step step);

	const std::u32string ToString(TeamType team);

	const char ToChar(TileType tile);
}