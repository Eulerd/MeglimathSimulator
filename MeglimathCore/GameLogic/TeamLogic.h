#pragma once
#include "Types.h"
#include "Agent.h"
#include <array>
struct TeamLogic
{	
	// �t�B�[���h //
	/// <summary>
	/// �`�[��A,B�𔻒f���邽�߂̃`�[���̎��
	/// </summary>
	TeamType type;

	/// <summary>
	/// �`�[���ɏ�������G�[�W�F���g
	/// </summary>
	std::array<Agent,2> agents;

	// ���\�b�h //
	/// <summary>
	/// �G�[�W�F���g�̏����ʒu������������
	/// </summary>
	/// <param name="pos1">�G�[�W�F���g1�̏������W</param>
	/// <param name="pos2">�G�[�W�F���g2�̏������W</param>
	void InitAgentsPos(_Point<> pos1, _Point<> pos2)
	{
		agents = { { { pos1 },{ pos2 } } };
	}

	/// <summary>
	/// �w��̃G�[�W�F���g�𓮂���
	/// </summary>
	/// <param name="idx">�G�[�W�F���g�̔ԍ�</param>
	/// <param name="dir">����������</param>
	void MoveAgent(int idx, Direction dir)
	{
		agents[idx].Move(dir);
	}

	/// <summary>
	/// �w����W�ɂ���G�[�W�F���g�𓮂���
	/// </summary>
	/// <param name="pos">�G�[�W�F���g�̂�����W</param>
	/// <param name="dir">����������</param>
	void MoveAgent(_Point<> pos, Direction dir)
	{
		for (auto & agent : agents)
		{
			if (agent.position == pos)
			{
				agent.Move(dir);
				return;
			}
		}
	}

};

