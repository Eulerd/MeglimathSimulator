#pragma once
#include <Siv3D.hpp>

enum class TileType
{
	A, B, None
};

enum class TeamType
{
	A, B
};

namespace Tile
{
	/// <summary>
	/// �^�C���̐F���擾����
	/// </summary>
	Color ColorOf(TileType t_type);
}