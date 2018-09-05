#pragma once
#include "../MeglimathCore/GameLogic/Think.h"
#include "../MeglimathCore/GameInfo.h"

class Client
{
protected:
	TeamType _type;

public:
	/// <summary>
	/// �G�[�W�F���g�̎��̍s�����Q�[���������Ɏ�������
	/// </summary>
	/// <param name="info">���J�����Q�[�����</param>
	/// <returns>�G�[�W�F���g�̎��̍s��</returns>
	virtual Think NextThink(GameInfo info) = 0;

	virtual void Update() = 0;

	bool IsReady();

protected:
	bool _is_ready = false;

public:
	Client();
	Client(TeamType type);
	~Client();
};

