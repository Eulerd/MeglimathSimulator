#pragma once
#include "GameInfo.h"
#include "Think.h"
#include "TeamType.h"
#include "Agent.h"

class Team
{
private:
	int _total_point;
	Agent _agents[2];
	TeamType _type;

public:
	virtual Think NextThink(GameInfo info);

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

