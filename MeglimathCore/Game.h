#pragma once
#include "Drawer.h"
#include "Field.h"
#include "Team.h"
#include "DrawingInfo.h"

class Game
{
private:
	Field _field;
	Team _teams[2];

	/// <summary>
	/// �`�[�����Ƃ̂��ׂẴG�[�W�F���g�̍s�����X�g
	/// </summary>
	HashTable<TeamType, Think> _thinks;

private:
	/// <summary>
	/// �G�[�W�F���g�������_���ɏ���������
	/// </summary>
	void initAgentsPos();

	/// <summary>
	/// �G�[�W�F���g�̏������������s��
	/// </summary>
	/// <param name="init_pos">�G�[�W�F���g�̏������W�̂��ƂɂȂ鍶��̍��W</param>
	void initAgentsPos(Point init_pos);

public:
	/// <summary>
	/// �Q�[�������擾����
	/// </summary>
	/// <returns>�t�B�[���h�ƃG�[�W�F���g�̏��</returns>
	GameInfo GetGameInfo() const;

	Field GetField() const;

	HashTable<TeamType, Think> GetThinks() const;

	/// <summary>
	/// �Q�[�������̃^�[���ɐi�߂�
	/// </summary>
	void NextTurn();

	/// <summary>
	/// �Q�[���̏�Ԃ��X�V����
	/// ���ׂẴG�[�W�F���g�����擾����
	/// </summary>
	/// <returns>���ׂẴG�[�W�F���g��񃊃X�g</returns>
	Array<Agent> GetAgents() const;

	/// <summary>
	/// �`�[�����Ƃ̃G�[�W�F���g�̏����擾����
	/// </summary>
	/// <returns>�`�[�����Ƃ̃G�[�W�F���g���</returns>
	HashTable<TeamType, Array<Agent>> GetAgentMap() const;

	/// <summary>
	/// �Q�[�����X�V����
	/// </summary>
	void Update();

public:
	Game(const String path);

	virtual ~Game();
};
