#pragma once

#include "Client.h"
#include "../MeglimathCore/Utility.h"
#include "../MeglimathCore/GameLogic/Think.h"

class DoubleNextBestClient2 :
	public Client
{
public:
	DoubleNextBestClient2() {}
	DoubleNextBestClient2(TeamType type):Client(type) {}

	String Name() override
	{
		return U"DoubleNextBest2";
	}

	void Initialize() override
	{
		_is_ready = false;
	}

	void Update(GameInfo info) override;
private:
	int double_stop_cnt = 0;		// �����̃G�[�W�F���g�����̍s�����A�����ĉ��񎸔s���������J�E���g����

	_Point<> pos_history[2] = { _Point<>(), _Point<>() };		// �O�̃^�[�������̃G�[�W�F���g���ǂ��ɂ�����

	long long  Explore(const GameInfo& info, const GameLogic& game, int depth);

	static constexpr int DOUBLE_STOP_LIMIT = 2;		// �����̃G�[�W�F���g�����̍s���̎��s���A������ DOUBLE_STOP_LIMIT ��𒴂����ꍇ���򐨎��ɑË��������ł�
	static constexpr int DOUBLE_STOP_LIMIT_FORCE = 5;		// �����̃G�[�W�F���g�����̍s���̎��s���A������ DOUBLE_STOP_LIMIT_FORCE ��𒴂����ꍇ�����_���Ȏ��ł�
	static constexpr int EXPLORE_DEPTH = 2;		// �T���̐[�� = �����܂œǂނ�
};