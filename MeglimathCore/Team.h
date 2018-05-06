#pragma once
#include "GameInfo.h"
#include "Think.h"
#include "Types.h"
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

public:
	int GetTotalPoint() const;
	void SetTotalPoint(int total_point);

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
	/// <param name="agent1">��l�ڂ̃G�[�W�F���g�̏������W</param>
	/// <param name="agent2">��l�ڂ̃G�[�W�F���g�̏������W</param>
	Team(Point pos1, Point pos2);

	virtual ~Team();
};

