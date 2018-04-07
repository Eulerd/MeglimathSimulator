#pragma once
#include "Cell.h"
#include "Transform.h"

class Field
{
private:
	Grid<Cell> _cells;
	Point _origin;

	/// <summary>
	/// �Z���������̑傫��
	/// </summary>
	const Size _c_size = Size(32, 32);

public:
	void Draw() const;

	Grid<Cell> GetCells();

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
	/// <param name="origin">���_</param>
	/// <param name="size">�t�B�[���h�̑傫��</param>
	Field(Point origin, Size size);

	Field(Size size);
	virtual ~Field();
};
