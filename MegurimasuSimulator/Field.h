#pragma once
#include "Cell.h"
#include "Transform.h"

class Field
{
private:
	/// <summary>
	/// �t�B�[���h���
	/// </summary>
	Grid<Cell> _cells;

	/// <summary>
	/// �̈�|�C���g���v�Z����Ƃ��T�����������i�[����
	/// </summary>
	Grid<bool> _status;

private:
	/// <summary>
	/// �͂܂�Ă���̈��T������
	/// </summary>
	/// <param name="pos">�T�����J�n������W</param>
	/// <param name="tile">�ǂ̃^�C���ň͂܂�Ă��邩</param>
	void dfsAreaPoint(Point pos, TileType tile);

public:
	/// <summary>
	/// �t�B�[���h�𐶐����܂�
	/// </summary>
	/// <param name="file">�t�B�[���h���̂���json�t�@�C��</param>
	/// <returns>���������t�B�[���h</returns>
	static Field Create(FilePath file);

	/// <summary>
	/// �w��̃^�C���ň͂܂ꂽ�̈�̓��_���v�Z���܂�
	/// </summary>
	/// <param name="tile">�ǂ̃^�C���ň͂܂�Ă��邩</param>
	/// <returns>�̈�|�C���g</returns>
	int GetAreaPoint(TileType tile);

	/// <summary>
	/// �Z�������擾����
	/// </summary>
	/// <returns>�t�B�[���h�̃Z�����</returns>
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

	/// <summary>
	/// �w����W���t�B�[���h�̒��ł��邩���肷��
	/// </summary>
	/// <param name="pos">�t�B�[���h�������肷����W</param>
	/// <returns>���W���t�B�[���h���ł��邩</returns>
	bool IsInField(Point pos);

public:
	Field();

	void operator=(const Field& other);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="size">�t�B�[���h�̑傫��</param>
	Field(Size size);

	/// <summary>
	/// �Z�������Ƀt�B�[���h�𐶐�����R���X�g���N�^
	/// </summary>
	/// <param name="cells">���ƂȂ�Z��</param>
	Field(Grid<Cell> cells);

	virtual ~Field();
};
