#pragma once
#include "GameLogic/Field.h"
#include "DrawingInfo.h"
#include "GameLogic/Think.h"
#include <Siv3D.hpp>

class Drawer : public DrawingInfo
{
public:
	/// <summary>
	/// �t�B�[���h��`�悷��
	/// </summary>
	/// <param name="field">�`�悷��t�B�[���h</param>
	void DrawField(const Field & field) const;

	/// <summary>
	/// ���ׂẴG�[�W�F���g��`�悷��
	/// </summary>
	/// <param name="agents">�G�[�W�F���g���X�g</param>
	void DrawAgents(HashTable<TeamType, Array<Agent>> agents) const;

	/// <summary>
	/// �G�[�W�F���g�̍s����^�[������\������
	/// </summary>
	/// <param name="thinks">���ׂẴG�[�W�F���g�̍s��</param>
	/// <param name="turn">�c��^�[����</param>
	/// <param name="field">�`�[���̍��v���_��`�悷�邽�߂̃t�B�[���h���</param>
	void DrawStatus(const HashTable<TeamType, Think> & thinks, const Field & field, int turn) const;

public:
	Drawer();
	~Drawer();
};

