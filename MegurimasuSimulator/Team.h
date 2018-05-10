#pragma once
#include "GameInfo.h"
#include "Think.h"
#include "Types.h"
#include "Agent.h"
#include "TeamLogic.h"
class Team
{
protected:
	TeamLogic & _team;
public:
	/// <summary>
	/// �G�[�W�F���g�̎��̍s�����Q�[���������Ɏ�������
	/// </summary>
	/// <param name="info">���J�����Q�[�����</param>
	/// <returns>�G�[�W�F���g�̎��̍s��</returns>
	virtual Think NextThink(GameInfo info) = 0;

	/// <summary>
	/// �`�[����Think�f�[�^�̊i�[���������Ă��邩
	/// </summary>
	virtual bool IsReady() = 0;

	virtual void Update(const Field & field) = 0;
	
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Team(TeamLogic & team);
	virtual ~Team();
};

