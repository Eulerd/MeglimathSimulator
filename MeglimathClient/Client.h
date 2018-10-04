#pragma once
#include "../MeglimathCore/GameLogic/Think.h"
#include "../MeglimathCore/GameInfo.h"

class Client
{
protected:
	TeamType _type;
	Think _think;

public:
	Think GetNextThink();

public:
	/// <summary>
	/// ���̍s�������肷��
	/// </summary>
	/// <param name="info">�Q�[�����</param>
	virtual void Update(GameInfo info) = 0;

	/// <summary>
	/// ���̃^�[���ɓ���O�̏���������
	/// </summary>
	virtual void Initialize() = 0;

	bool IsReady();

protected:
	bool _is_ready = false;

public:
	Client();
	Client(TeamType type);
	~Client();
};

