#pragma once
#include "Agent.h"
#include "TeamType.h"

class Cell
{
private:
	/// <summary>
	/// �}�X�ɂ͂߂�ꂽ�^�C��
	/// </summary>
	TileType _tile;

	/// <summary>
	/// �}�X�̓_��
	/// </summary>
	int _point;

public:
	/// <summary>
	/// �w��̃`�[���ɂ���ăZ���Ƀ^�C�����u�����
	/// </summary>
	/// <param name="team">�Z���Ƀ^�C����u���`�[��</param>
	void PaintedBy(TeamType team);

public:
	Cell();
	Cell(int point);
	virtual ~Cell();

};
