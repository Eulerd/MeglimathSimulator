#pragma once
#include"Think.h"
#include "Field.h"
#include"TeamLogic.h"
class GameLogic
{
private:
	Field _field;
	int _turn;
	Array<TeamLogic> _teamlogics;

public:

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
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json�t�@�C���ւ̃p�X</param>
	void InitalizeFromJson(const String path);

	int GetTurn() const;

	Field GetField() const;

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
	/// �Q�[�������̃^�[���ɐi�߂�
	/// </summary>
	void NextTurn(HashTable<TeamType, Think> &_thinks);


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="team_a">�`�[��A�̏��</param>
	/// <param name="team_b">�`�[��B�̏��</param>
	GameLogic();

	virtual ~GameLogic();
};
