#pragma once
#include"Think.h"
#include "Field.h"
#include"TeamLogic.h"
#include<unordered_map>
#include<vector>
#include <rapidjson\document.h>

class GameLogic
{
private:
	int _turn = 60;
	Field _field;
	std::array<TeamLogic, 2> teams = {};

public:

	/// <summary>
	/// �G�[�W�F���g�������_���ɏ���������
	/// </summary>
	void initAgentsPos();

	/// <summary>
	/// �G�[�W�F���g�̏������������s��
	/// </summary>
	/// <param name="init_pos">�G�[�W�F���g�̏������W�̂��ƂɂȂ鍶��̍��W</param>
	void initAgentsPos(_Point<> init_pos);

	void initAgentsPos(_Point<> init_pos1, _Point<> init_pos2);

	void initAgentPos(std::array<_Point<>,4> init_pos);

public:
	/// <summary>
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json</param>
	void InitalizeFromJson(const std::string json);

	void InitializeRandom(int turn, int height, int width);
	void InitializeVariable(int turn, const Field& field, const std::array<TeamLogic, 2>& teams);
	int GetTurn() const;
	std::array<TeamLogic, 2> GetTeams()const;
	const Field& GetField() const;

	/// <summary>
	/// �Q�[���̏�Ԃ��X�V����
	/// ���ׂẴG�[�W�F���g�����擾����
	/// </summary>
	/// <returns>���ׂẴG�[�W�F���g��񃊃X�g</returns>
	std::vector<Agent> GetAgents() const;

	/// <summary>
	/// �Q�[�������̃^�[���ɐi�߂�
	/// </summary>
	void NextTurn(const std::unordered_map<TeamType, Think> &_thinks);

	///<summary>
	///�\�ȍs����
	///</summary>
	bool IsThinkAble(TeamType team, Think think)const;

	bool GetGameEnd();
	int GetWinner();
};
