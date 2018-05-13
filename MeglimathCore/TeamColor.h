#pragma once
#include <Siv3D.hpp>
#include"GameLogic/GameLogic.h"
namespace TeamColor
{
	constexpr Color A = Palette::Blue;
	constexpr Color B = Palette::Red;

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
			return TeamColor::A;
		case TileType::B:
			return TeamColor::B;
		case TileType::None:
		default:
			return Palette::White;
		}
	}

	constexpr Color ColorOf(TeamType t_type)
	{
		switch (t_type)
		{
		case TeamType::A:
			return TeamColor::A;
		case TeamType::B:
			return TeamColor::B;
		default:
			return Palette::Darkgray;
		}
	}
}
