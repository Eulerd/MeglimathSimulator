#pragma once
#include "Cell.h"
#include "Transform.h"

class Field
{
private:
	Grid<Cell> _cells;

public:
	Grid<Cell> GetCells() const;

	/// <summary>
	/// �Z����h��
	/// </summary>
	/// <param name="pos">�h��Z���̍��W</param>
	/// <param name="team">�Z����h��`�[��</param>
	void PaintCell(Point pos, TeamType team);

	/// <summary>
	/// �^�C�������
	/// </summary>
	/// <param name="pos">�^�C���̍��W</param>
	void RemoveTile(Point pos);

public:
	Field();

	void operator=(const Field& other);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="size">�t�B�[���h�̑傫��</param>
	Field(Size size);

	virtual ~Field();
};
