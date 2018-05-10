#pragma once
#include "Drawer.h"
#include "GameLogic/Field.h"
#include "Team.h"
#include "DrawingInfo.h"
#include"GameLogic/TeamLogic.h"
#include"GameLogic/GameLogic.h"
class Game
{
private:
	GameLogic _gamelogic;

	/// <summary>
	/// 2�`�[���̏��
	/// </summary>
	Array<std::shared_ptr<Team>> _teams;

	/// <summary>
	/// �`�[�����Ƃ̂��ׂẴG�[�W�F���g�̍s�����X�g
	/// </summary>
	HashTable<TeamType, Think> _thinks;

private:
	/// <summary>
	/// �Q�[�������擾����
	/// </summary>
	/// <returns>�t�B�[���h�ƃG�[�W�F���g�̏��</returns>
	GameInfo getGameInfo() const;

	/// <summary>
	/// �G�[�W�F���g�������_���ɏ���������
	/// </summary>
	void initAgentsPos();

	/// <summary>
	/// �G�[�W�F���g�̏������������s��
	/// </summary>
	/// <param name="init_pos">�G�[�W�F���g�̏������W�̂��ƂɂȂ鍶��̍��W</param>
	void initAgentsPos(Point init_pos);

public:
	void setTeam(std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b);
	Array<TeamLogic>& getTeamLogics();
	/// <summary>
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json�t�@�C���ւ̃p�X</param>
	void InitalizeFromJson(const String path);

	bool IsReady();

	/// <summary>
	/// �^�[�������擾����
	/// </summary>
	/// <returns>���݂̃^�[��</returns>
	int GetTurn() const;

	Field GetField() const;

	HashTable<TeamType, Think> GetThinks() const;

	/// <summary>
	/// �Q�[�������̃^�[���ɐi�߂�
	/// </summary>
	void NextTurn();

	/// <summary>
	/// �Q�[���̏�Ԃ��X�V����
	/// ���ׂẴG�[�W�F���g�����擾����
	/// </summary>
	/// <returns>���ׂẴG�[�W�F���g��񃊃X�g</returns>
	Array<Agent> GetAgents() const;

	/// <summary>
	/// �`�[�����Ƃ̃G�[�W�F���g�̏����擾����
	/// </summary>
	/// <returns>�`�[�����Ƃ̃G�[�W�F���g���</returns>
	HashTable<TeamType, Array<Agent>> GetAgentMap() const;

	/// <summary>
	/// �Q�[�����X�V����
	/// </summary>
	void Update();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="team_a">�`�[��A�̏��</param>
	/// <param name="team_b">�`�[��B�̏��</param>
	Game();

	virtual ~Game();
};
