#include "Field.h"

Field Field::Create(FilePath file)
{
	JSONReader json(file);

	Size size = json[U"Size"].get<Size>();
	auto points = json[U"Points"].arrayView();

	// ���͂����^�C���|�C���g�̐�
	Size data_size = Size((size.x + 1) / 2, (size.y + 1) / 2);

	Grid<Cell> cells = Grid<Cell>(size);

	// �^�C���|�C���g���O���b�h��ɐ��^���ē���
	int idx = 0;
	for (int i : step(data_size.x))
	{
		for (int k : step(data_size.y))
		{
			cells[k][i] = points[idx].get<int>();
			// �f�[�^���R�s�[
			cells[size.y - 1 - k][size.x - 1 - i] = cells[k][i];

			idx++;
		}
	}

	return Field(cells);
}

Grid<Cell> Field::GetCells() const
{
	return _cells;
}

void Field::PaintCell(Point pos, TeamType team)
{
	_cells[pos.y][pos.x].PaintedBy(team);
}

void Field::RemoveTile(Point pos)
{
	_cells[pos.y][pos.x].RemoveTile();
}

bool Field::IsInField(Point pos)
{
	return (0 <= pos.x && pos.x < _cells.width()) && (0 <= pos.y && pos.y < _cells.height());
}

Field::Field()
{
}

void Field::operator=(const Field & other)
{
	_cells = other._cells;
}


Field::Field(Size size)
{
	_cells = Grid<Cell>(size);
}

Field::Field(Grid<Cell> cells)
{
	_cells = cells;
}

Field::~Field()
{
}
