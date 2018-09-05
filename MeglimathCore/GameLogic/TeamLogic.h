#pragma once
#include "Types.h"
#include "Agent.h"
#include <array>
class TeamLogic
{
private:
	/// <summary>
	/// �`�[���ɏ�������G�[�W�F���g
	/// </summary>
	std::array<Agent,2> agents;

	/// <summary>
	/// �`�[��A,B�𔻒f���邽�߂̃`�[���̎��
	/// </summary>
	TeamType _type;

public:
	/// <summary>
	/// �G�[�W�F���g�̏����ʒu������������
	/// </summary>
	/// <param name="pos1">�G�[�W�F���g1�̏������W</param>
	/// <param name="pos2">�G�[�W�F���g2�̏������W</param>
	void InitAgentsPos(_Point<> pos1, _Point <>pos2);

	const std::array<Agent, 2>& GetAgents() const;

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
	void MoveAgent(_Point<> pos, Direction dir);
	TeamType getTeamType() const;
public:
	TeamLogic();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�`�[���̎��</param>
	/// <param name="agent1">��l�ڂ̃G�[�W�F���g</param>
	/// <param name="agent2">��l�ڂ̃G�[�W�F���g</param>
	TeamLogic(TeamType type, Agent agent1, Agent agent2);

	//�R�s�[�R���X�g���N�^
	TeamLogic(const TeamLogic &tl);
};

