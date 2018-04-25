#pragma once
#include "Team.h"
class KeyBoardTeam :
	public Team
{
public:
	Think NextThink(GameInfo info) override
	{
		Think think;
		for (int i : step(2))
		{
			if (!_next_steps[i].has_value())
			{
				return Think{ Step{Action::Stop}, Step{Action::Stop} };
			}

			think.steps[i] = _next_steps[i].value();
			// ���̍X�V�̂��߂ɏ�����
			_next_steps[i].reset();
		}
		_is_ready = false;
		
		return think;
	}

	bool IsReady() override
	{
		return _is_ready;
	}

private:
	/// <summary>
	/// �L�[���͂����ꂽ���̍s�����i�[���Ă���
	/// </summary>
	Optional<Step> _next_steps[2];

	/// <summary>
	/// ���ׂĂ̍s�����I���ς݂ł��邩�𔻒肷��
	/// </summary>
	bool _is_ready = false;

private:
	/// <summary>
	/// �L�[���͂ɂ���čs��������������߂�B���͂������Ȃ������ꍇ�̂��߂�Optional�Ƃ���
	/// </summary>
	/// <returns>�L�[���͂ɂ���Č��߂�ꂽ����</returns>
	Optional<Direction> DecideDirectionByKey();

public:
	void Update(const Field & field);

public:
	KeyBoardTeam(TeamType type);
	KeyBoardTeam(TeamType type, Agent agent1, Agent agent2);
	~KeyBoardTeam();
};

