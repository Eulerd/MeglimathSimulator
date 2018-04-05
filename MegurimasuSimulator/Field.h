#pragma once
#include "Cell.h"

class Field
{
private:
	Grid<Cell> _cells;
	Point _origin;

	/// <summary>
	/// �Z���������̑傫��
	/// </summary>
	const Size _c_size = Size(32, 32);

	const Font _font{ _c_size.x / 2 };

public:
	void Draw() const;


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
