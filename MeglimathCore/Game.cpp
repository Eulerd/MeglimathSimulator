﻿#include "Game.h"
#include"LogicUtil.h"
GameInfo Game::GetGameInfo() const
{
	return GameInfo(_gamelogic.GetField(), _gamelogic.GetTurn(), LogicUtil::toS3dHashTable(_gamelogic.GetTeams()));
}

HashTable<TeamType, Array<Agent>> Game::GetAgentMap() const
{
	return LogicUtil::toS3dHashTable(_gamelogic.GetTeams());
}

void Game::Redo()
{
	if (_redo.empty())return;

	_undo.push(_gamelogic);

	_gamelogic = _redo.top();
	_redo.pop();
}

void Game::Undo()
{
	if (_undo.empty()) return;

	_redo.push(_gamelogic);
	_gamelogic = _undo.top();
	_undo.pop();
}

void Game::SpinRight90()
{
	_gamelogic.SpinRight90();
}

void Game::SpinLeft90()
{
	_gamelogic.SpinLeft90();
}


Array<Agent> Game::GetAgents() const
{
	return LogicUtil::toS3dArray<Agent>(_gamelogic.GetAgents());
}

void Game::initAgentsPos()
{
	Size size = LogicUtil::toS3dPoint(_gamelogic.GetField().cells.size());

	initAgentsPos(Point(Random((size.x - 2) / 2), Random((size.y - 2) / 2)));
}

void Game::initAgentsPos(Point init_pos)
{
	_gamelogic.initAgentsPos({ init_pos.x,init_pos.y });
}

Game::Game(const String field_json)
{
	_gamelogic.InitalizeFromJson(field_json.narrow());
}

int Game::GetTurn() const
{
	return _gamelogic.GetTurn();
}
void Game::NextTurn(Think team_blue, Think team_red)
{
	if (_gamelogic.GetTurn() <= 0)
	{
		return;
	}

	_undo.push(_gamelogic);
	while (!_redo.empty()) _redo.pop();
	
	GameInfo info = GetGameInfo();
	auto agents_map = GetAgentMap();
	auto agents = GetAgents();
	
	_think_table[TeamType::Blue] = team_blue;
	_think_table[TeamType::Red] = team_red;

	_gamelogic.NextTurn(LogicUtil::fromS3dHashTable(_think_table));
}

Field Game::GetField() const
{
	return _gamelogic.GetField();
}

HashTable<TeamType, Think> Game::GetThinks() const
{
	return _think_table;
}

Game::Game()
{

}

Game::~Game()
{
}
