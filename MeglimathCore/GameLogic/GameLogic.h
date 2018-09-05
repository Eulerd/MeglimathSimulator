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
	Field _field;
	int _turn;
	std::vector<TeamLogic> _teamlogics;

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

	void initAgentPos(std::vector<_Point<>> init_pos);

public:
	const std::vector<TeamLogic>& getTeamLogics()const;
	/// <summary>
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json</param>
	void InitalizeFromJson(const std::string json);

	int GetTurn() const;

	Field GetField() const;

	/// <summary>
	/// �Q�[���̏�Ԃ��X�V����
	/// ���ׂẴG�[�W�F���g�����擾����
	/// </summary>
	/// <returns>���ׂẴG�[�W�F���g��񃊃X�g</returns>
	std::vector<Agent> GetAgents() const;

	/// <summary>
	/// �`�[�����Ƃ̃G�[�W�F���g�̏����擾����
	/// </summary>
	/// <returns>�`�[�����Ƃ̃G�[�W�F���g���</returns>
	std::unordered_map<TeamType, std::array<Agent, 2>> GetAgentMap() const;

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

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameLogic();
	GameLogic(int turn);
	GameLogic(int turn, _Size size);
	GameLogic(const GameLogic& gamelogic);
	GameLogic(const Field &field, int t, const std::vector<TeamLogic>& tl);
	virtual ~GameLogic();
};
