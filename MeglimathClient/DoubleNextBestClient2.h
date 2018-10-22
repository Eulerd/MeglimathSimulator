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

	int double_stop_cnt = 0;		// �����̃G�[�W�F���g�����̍s�����A�����ĉ��񎸔s���������J�E���g����
	const int DOUBLE_STOP_LIMIT = 2;		// �����̃G�[�W�F���g�����̍s���̎��s���A������ DOUBLE_STOP_LIMIT ��𒴂����ꍇ���򐨎��ɑË��������ł�
	// DOUBLE_STOP_LIMIT_FORCE �� �����������(�����ɂ���)�\��
	const int DOUBLE_STOP_LIMIT_FORCE = 5;		// �����̃G�[�W�F���g�����̍s���̎��s���A������ DOUBLE_STOP_LIMIT_FORCE ��𒴂����ꍇ�����_���Ȏ��ł�
	static const int EXPLORE_DEPTH = 2;		// �T���̐[�� = �����܂œǂނ�

	_Point<> pos_history[2] = { _Point<>(), _Point<>() };		// �O�̃^�[�������̃G�[�W�F���g���ǂ��ɂ�����
	Array<Think> candidates[2];		// candidates[n] �� (n+1)�ԖڂɗD�悳���s���̌�⃊�X�g

	int eval_points[2] = { -100000, -100000 };		// eval_points[n] �� (n+1)�ԖڂɗD�悳��� 1���̍s�� �̕]���l
	int eval_points_next[EXPLORE_DEPTH];		// eval_points_next[n] �� (n+1)���̍s�� �̕]���l


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
	void Explore(const GameInfo& info, const GameLogic& game, int depth, int s1, int s2);
};