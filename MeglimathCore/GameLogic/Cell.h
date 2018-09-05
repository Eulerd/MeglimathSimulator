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
	void PaintedBy(TeamType team);

	/// <summary>
	/// �u���ꂽ�^�C�������
	/// </summary>
	void RemoveTile();
};
