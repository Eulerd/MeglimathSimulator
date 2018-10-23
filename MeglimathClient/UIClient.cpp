﻿#include "UIClient.h"



void UIClient::turn_init(const GameInfo & info)
{
	auto agents = info.GetAgents(_type);
	for (auto i : step(2))
	{
		agent_points[i] = { agents[i].position.x, agents[i].position.y };
	}

	auto& field = info.GetField();
	Size size = { field.cells.width(), field.cells.height() };

	if (field_ui.size() == size)
	{
		return;
	}

	// UI初期化
	field_ui = Grid<Rect>(size);
	const Point origin = Window::Center() - draw_size * (size / 2);
	for (auto y = 0; y < size.y; y++)
	{
		for (auto x = 0; x < size.x; x++)
		{
			Point pos(x, y);
			Point draw_pos = origin + Point(pos * draw_size);

			field_ui[y][x] = Rect(draw_pos, draw_size);
		}
	}
}

UIClient::UIClient(TeamType type)
{
	_type = type;
}
