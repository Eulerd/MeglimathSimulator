#include"DoubleNextBestClient2.h"
long long DoubleNextBestClient2::Explore(const GameInfo& info, const GameLogic& game, int depth)
{
	auto this_team = _type;
	auto other_team = Transform::GetInverseTeam(this_team);

	const auto all_step = Utility::AllStep();

	if (depth == 0)
	{
		auto eval_point_total = 0;		// eval_point_total �� eval_points_next �̑��a, ���̈��̕]���
		for (int e : eval_points_next)
			eval_point_total += e;

		if (!game.GetField().IsSameStateField(info.GetField()))		//�����̃G�[�W�F���g���m�̏Փ˂����o
		{
			for (int it = 0; it < 2; it++)
			{
				if (eval_points[it] <= eval_point_total)
				{
					if (eval_points[it] != eval_point_total)
						candidates[it].clear();

					eval_points[it] = eval_point_total;
					candidates[it].push_back({ all_step[s1], all_step[s2] });
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < all_step.size(); i++)
		{
			for (int k = 0; k < all_step.size(); k++)
			{
				auto next_game = game;
				std::unordered_map<TeamType, Think> thinks;
				thinks[this_team] = Think{ all_step[i],all_step[k] };
				thinks[other_team] = Think{ Step{Action::Stop,Direction::Stop},Step{Action::Stop,Direction::Stop} };
				next_game.NextTurn(thinks);
				auto points = next_game.GetField().GetTotalPoints();
				eval_points_next[depth - 1] = points[this_team] - points[other_team];

				if (depth == EXPLORE_DEPTH)
					Explore(info, next_game, depth - 1, i, k);		// �ŏ��̂� ������ s1, s2 ���X�V
				else
					Explore(info, next_game, depth - 1, s1, s2);
			}
			else {
				p = Explore(info, next_game, depth - 1);
			}
			if (p > maxp)maxp = p;
		}
	}
	return maxp;
}

void DoubleNextBestClient2::Update(GameInfo info)
{
	auto agents = info.GetAgents(_type);
	auto game = info.GetGameLogic();
	auto point = game.GetField().GetTotalPoints();
	auto this_team = _type;
	auto other_team = Transform::GetInverseTeam(this_team);

	const auto all_step = Utility::AllStep();
	// �����̃`�[���̃G�[�W�F���g�����̍s�����A���Ŏ��s�������𐔂���
//�v�C�� ���� : [�ړ����Ă��Ȃ�] -> [�ՖʂɕύX���Ȃ�]
	if (!(pos_history[0] == agents[0].position)
		|| !(pos_history[1] == agents[1].position))
		double_stop_cnt = 0;
	else
		double_stop_cnt++;

	pos_history[0] = agents[0].position;
	pos_history[1] = agents[1].position;

	long long  maxp[2] = { -10000000,-10000000 };
	int maxi[2], maxk[2];
	for (int i = 0; i < all_step.size(); i++)
	{
		long long  p = 0;
		for (int k = 0; k < all_step.size(); k++)
		{
			auto next_game = game;
			std::unordered_map<TeamType, Think> thinks;
			thinks[this_team] = Think{ all_step[i],all_step[k] };
			thinks[other_team] = Think{ Step{Action::Stop,Direction::Stop},Step{Action::Stop,Direction::Stop} };
			next_game.NextTurn(thinks);
			p = Explore(info, next_game, EXPLORE_DEPTH - 1);
			if (p > maxp[0]) {
				maxp[1] = maxp[0]; maxi[1] = maxi[0]; maxk[1] = maxk[0];
				maxp[0] = p; maxi[0] = i; maxk[0] = k;
			}
			else if (p > maxp[1]) {
				maxp[1] = p; maxi[1] = i; maxk[1] = k;
			}
		}
	}
	Think next_thinks[2] = {
		Think{ all_step[maxi[0]],all_step[maxk[0]] },
		Think{ all_step[maxi[1]],all_step[maxk[1]] }
	};

	// �򐨎��ɗ����̃G�[�W�F���g�����~�߂���Ă���ꍇ�A�Ë����ĂQ�Ԗڂɗǂ����ł�
	if (double_stop_cnt > DOUBLE_STOP_LIMIT_FORCE)
		_think =
	{
		Step{ Action(Random(0, 1)), Direction(Random(0, 7)) },
		Step{ Action(Random(0, 1)), Direction(Random(0, 7)) }
	};
	else if (double_stop_cnt > DOUBLE_STOP_LIMIT &&  point[this_team] < point[other_team])
		_think = next_thinks[1];
	else
		_think = next_thinks[0];

	_is_ready = true;
}