#include "Game.h"

GameInfo Game::getGameInfo() const
{
	return GameInfo(_gamelogic.GetField(), _gamelogic.GetAgentMap());
}

HashTable<TeamType, Array<Agent>> Game::GetAgentMap() const
{

	return _gamelogic.GetAgentMap();
}

Array<Agent> Game::GetAgents() const
{
	return _gamelogic.GetAgents();
}

void Game::initAgentsPos()
{
	Size size = _gamelogic.GetField().GetCells().size();

	initAgentsPos(Point(Random((size.x - 2) / 2), Random((size.y - 2) / 2)));
}

void Game::initAgentsPos(Point init_pos)
{
	_gamelogic.initAgentsPos(init_pos);
}

void Game::setTeam(std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b)
{
	_teams.append({ team_a, team_b });
}

Array<TeamLogic>& Game::getTeamLogics()
{
	return _gamelogic.getTeamLogics();
}

void Game::InitalizeFromJson(const String path)
{
	_gamelogic.InitalizeFromJson(path);
}

bool Game::IsReady()
{
	return _teams[0]->IsReady() && _teams[1]->IsReady();
}

int Game::GetTurn() const
{
	return _gamelogic.GetTurn();
}

void Game::NextTurn()
{
	if (_gamelogic.GetTurn() <= 0)
	{
		return;
	}
	
	GameInfo info = getGameInfo();
	auto agents_map = GetAgentMap();
	auto agents = GetAgents();

	_thinks[TeamType::A] = Think(_teams[0]->NextThink(info));
	_thinks[TeamType::B] = Think(_teams[1]->NextThink(info));

	_gamelogic.NextTurn(_thinks);

}

void Game::Update()
{
	_teams[0]->Update(_gamelogic.GetField());
	_teams[1]->Update(_gamelogic.GetField());
}

Field Game::GetField() const
{
	return _gamelogic.GetField();
}

HashTable<TeamType, Think> Game::GetThinks() const
{
	return _thinks;
}

Game::Game()
{

}

Game::~Game()
{
}
