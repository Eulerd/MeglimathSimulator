#include "Field.h"

int Field::GetAreaPoint(TileType tile)
{
	_status = Grid<bool>(_cells.size() + Point(2, 2), true);

	dfsAreaPoint(Point(0, 0), tile);

	int area_point = 0;
	for (int i : step(_status.width()))
	{
		for (int k : step(_status.height()))
		{
			if (_status[k][i])
			{
				area_point += _cells[k - 1][i - 1].GetPoint();
			}
		}
	}

	return area_point;
}

void Field::dfsAreaPoint(Point pos, TileType tile)
{
	// �͈͊O�Ȃ�I��
	if (pos.x < 0 || pos.x > _cells.width() + 1
		|| pos.y < 0 || pos.y > _cells.height() + 1)
	{
		return;
	}

	// �T���ς݂Ȃ�I��
	if (_status[pos.y][pos.x] == false)
	{
		return;
	}

	_status[pos.y][pos.x] = false;
	if (pos.x == 0 || pos.x == _cells.width() + 1 ||
		pos.y == 0 || pos.y == _cells.height() + 1)
	{
		// �[�͒T���̂ݍs��
	}
	else if (_cells[pos.y - 1][pos.x - 1].GetTile() == tile)
	{
		// �������̃^�C�����u����Ă�����I��
		return;
	}

	Point delta[] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

	// �l���֒T������
	for (int i : step(4))
	{
		dfsAreaPoint(pos + delta[i], tile);
	}
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

Field::~Field()
{
}
