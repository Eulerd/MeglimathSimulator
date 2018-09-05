#pragma once
#include "Agent.h"
#include "Types.h"

struct Cell
{

	/// <summary>
	/// �}�X�̓_��
	/// </summary>
	int point = 0;

	// �t�B�[���h //
	/// <summary>
	/// �}�X�ɂ͂߂�ꂽ�^�C��
	/// </summary>
	TileType tile = TileType::None;

	// ���\�b�h //

	/// <summary>
	/// �w��̃`�[���ɂ���ăZ���Ƀ^�C�����u�����
	/// </summary>
	/// <param name="team">�Z���Ƀ^�C����u���`�[��</param>
	void PaintedBy(TeamType team)
	{
		switch (team)
		{
		case TeamType::A:
			tile = TileType::A;
			break;

		case TeamType::B:
			tile = TileType::B;
			break;
		}
	}

	/// <summary>
	/// �u���ꂽ�^�C�������
	/// </summary>
	void RemoveTile()
	{
		tile = TileType::None;
	}
};
