#pragma once
#include "Drawer.h"
#include "Field.h"
#include "Team.h"
#include "DrawingInfo.h"

class Game
{
private:
	Field _field;
	Drawer _drawer;
	int _turn;

	/// <summary>
	/// 2�`�[���̏��
	/// </summary>
	Array<std::shared_ptr<Team>> _teams;

	/// <summary>
	/// �`�[�����Ƃ̂��ׂẴG�[�W�F���g�̍s�����X�g
	/// </summary>
	std::map<TeamType, Think> _thinks;

private:
	/// <summary>
	/// �Q�[�������擾����
	/// </summary>
	/// <returns>�t�B�[���h�ƃG�[�W�F���g�̏��</returns>
	GameInfo getGameInfo() const;

	/// <summary>
	/// �`�[�����Ƃ̃G�[�W�F���g�̏����擾����
	/// </summary>
	/// <returns>�`�[�����Ƃ̃G�[�W�F���g���</returns>
	std::map<TeamType, Array<Agent>> getAgentMap() const;

	/// <summary>
	/// ���ׂẴG�[�W�F���g�����擾����
	/// </summary>
	/// <returns>���ׂẴG�[�W�F���g��񃊃X�g</returns>
	Array<Agent> getAgents() const;

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
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json�t�@�C���ւ̃p�X</param>
	void InitalizeFromJson(const String path);

	bool IsReady();

	/// <summary>
	/// �^�[�������擾����
	/// </summary>
	/// <returns>���݂̃^�[��</returns>
	int GetTurn() const;

	/// <summary>
	/// �Q�[�������̃^�[���ɐi�߂�
	/// </summary>
	void NextTurn();

	/// <summary>
	/// �Q�[���̏�Ԃ��X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[����`�悷��
	/// </summary>
	void Draw() const;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="team_a">�`�[��A�̏��</param>
	/// <param name="team_b">�`�[��B�̏��</param>
	Game(std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b);

	virtual ~Game();
};
