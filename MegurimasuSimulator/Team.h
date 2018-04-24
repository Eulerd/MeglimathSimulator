#pragma once
#include "GameInfo.h"
#include "Think.h"
#include "TeamType.h"
#include "Agent.h"

class Team
{
protected:
	/// <summary>
	/// �`�[���̍��v�|�C���g
	/// </summary>
	int _total_point;

	/// <summary>
	/// �`�[���ɏ�������G�[�W�F���g
	/// </summary>
	Agent _agents[2];

	/// <summary>
	/// �`�[��A,B�𔻒f���邽�߂̃`�[���̎��
	/// </summary>
	TeamType _type;

public:
	/// <summary>
	/// �G�[�W�F���g�̎��̍s�����Q�[���������Ɏ�������
	/// </summary>
	/// <param name="info">���J�����Q�[�����</param>
	/// <returns>�G�[�W�F���g�̎��̍s��</returns>
	virtual Think NextThink(GameInfo info) = 0;

	int GetTotalPoint() const;
	void SetTotalPoint(int total_point);

	/// <summary>
	/// �G�[�W�F���g�̏����ʒu������������
	/// </summary>
	/// <param name="pos1">�G�[�W�F���g1�̏������W</param>
	/// <param name="pos2">�G�[�W�F���g2�̏������W</param>
	void InitAgentsPos(Point pos1, Point pos2);

	Array<Agent> GetAgents() const;
	
	/// <summary>
	/// �w��̃G�[�W�F���g�𓮂���
	/// </summary>
	/// <param name="idx">�G�[�W�F���g�̔ԍ�</param>
	/// <param name="dir">����������</param>
	void MoveAgent(int idx, Direction dir);

	/// <summary>
	/// �w����W�ɂ���G�[�W�F���g�𓮂���
	/// </summary>
	/// <param name="pos">�G�[�W�F���g�̂�����W</param>
	/// <param name="dir">����������</param>
	void MoveAgent(Point pos, Direction dir);

public:
	Team();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�`�[���̎��</param>
	/// <param name="agent1">��l�ڂ̃G�[�W�F���g</param>
	/// <param name="agent2">��l�ڂ̃G�[�W�F���g</param>
	Team(TeamType type, Agent agent1, Agent agent2);
	virtual ~Team();
};

