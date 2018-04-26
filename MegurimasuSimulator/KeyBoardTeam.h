#pragma once
#include "WaitingForInputTeam.h"

class KeyBoardTeam :
	public WaitingForInputTeam
{
private:
	Array<Key> _operation_keys;

private:
	/// <summary>
	/// �L�[���͂ɂ���čs��������������߂�B���͂������Ȃ������ꍇ�̂��߂�Optional�Ƃ���
	/// </summary>
	/// <returns>�L�[���͂ɂ���Č��߂�ꂽ����</returns>
	Optional<Direction> decideDirectionByKey();

public:
	void Update(const Field & field);

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"></param>
	/// <param name="operation_keys">Right���甽���v���ɕ����L�[���w��</param>
	KeyBoardTeam(TeamType type, Array<Key> operation_keys);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"></param>
	/// <param name="agent1"></param>
	/// <param name="agent2"></param>
	/// <param name="operation_keys">Right���甽���v���ɕ����L�[���w��</param>
	KeyBoardTeam(TeamType type, Agent agent1, Agent agent2, Array<Key> operation_keys);
	~KeyBoardTeam();
};

