#pragma once
#include<Siv3D.hpp>
#include "Drawer.h"
#include "GameInfo.h"
#include "DrawingInfo.h"
#include"GameLogic/GameLogic.h"
class Game
{
private:
	GameLogic _gamelogic;
	HashTable<TeamType, Think> _think_table;

private:
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
	Array<TeamLogic>& getTeamLogics();
	/// <summary>
	/// �Q�[�������擾����
	/// </summary>
	/// <returns>�t�B�[���h�ƃG�[�W�F���g�̏��</returns>
	GameInfo GetGameInfo() const;

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
	void NextTurn(Think team_a, Think team_b);

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

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="team_a">�`�[��A�̏��</param>
	/// <param name="team_b">�`�[��B�̏��</param>
	Game();


	/// <summary>
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json�t�@�C���ւ̃p�X</param>
	Game(const String path);

	virtual ~Game();
};
