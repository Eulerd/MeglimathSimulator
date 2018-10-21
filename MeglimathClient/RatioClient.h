#pragma once
#include "Client.h"

//TeamToTile�g�����߂̃C���N���[�h
#include "T_Monte_Carlo.h"

namespace RC {
	int movedByway(int way);
}

class RatioClient :
	public Client {
private:
	int lastMovedBy[2] = { 8,8 };//���݈ʒu�ɂ͂ǂ̃}�X���痈���̂����i�[���Ă����B
								 //�Ⴆ�΁A�O�̃^�[��0�̂̕����ɐi�ނ��Ƃɂ���Č��݂̃}�X�ɗ����̂Ȃ�A4���i�[�����
	int max[2] = { 8,8};//���ӂ̃}�X�̒��ň�ԃ|�C���g�������}�X
public:
	String Name() override {
		return U"RatioClient";
	}

	void Initialize() override {
		_is_ready = false;
	}

	//���ӂ̃}�X�̓��A��ԓ��_���傫���}�X�ɍs��
	//���ӂ̃}�X�̓��A����̃}�X����ԓ��_�̑傫���}�X�ł���΁A�������������B
	void Update(GameInfo info) override {

		//if (IsReady()) {
		//	return;
		//}

		Field tem = info.GetField();

		Array<Agent> agents = info.GetAgents(_type);

		_Point<> preP[2];

		//�������߂邽�߂̃|�C���g����Ƃ����
		int temppoint = -3;
		bool didnewway = false;//�V�������̎肪�i�[���ꂽ��

		for (int i = 0; i < 2; i++) {
			preP[i] = agents[i].position;
			for (int j = 0; j < 8; j++) {
				if (tem.IsInField(preP[i] + Transform::DirToDelta(Direction(j)))) {//�I�񂾃}�X���t�B�[���h����
					if (tem.cells[(preP[i] + Transform::DirToDelta(Direction(j))).y][(preP[i] + Transform::DirToDelta(Direction(j))).x].point > temppoint//���ݕۑ����Ă���ő�|�C���g���Q�Ƃ��Ă���|�C���g�̕����������ǂ���
						|| (tem.cells[(preP[i] + Transform::DirToDelta(Direction(j))).y][(preP[i] + Transform::DirToDelta(Direction(j))).x].point == temppoint && Random(0,100) % 2 == 0)) {//�����������烉���_��
						if ((lastMovedBy[i] == 8 || j != lastMovedBy[i]) && tem.cells[(preP[i] + Transform::DirToDelta(Direction(j))).y][(preP[i] + Transform::DirToDelta(Direction(j))).x].tile != TMC::TeamtoTile(_type)) {//�Ō�ɗ��������ɂ�����x�s���Ȃ��悤�ɁA�����̃}�X�͏��O
							if (i == 0 || (i == 1 && !(agents[0].position + Transform::DirToDelta(Direction(max[0])) == preP[i] + Transform::DirToDelta(Direction(j))))) {//�G�[�W�F���g���m���h�R���Ȃ��悤�ɁA��l�ڂ̃G�[�W�F���g���i�����Ƃ��Ă���}�X�ɂ͓�l�ڂ͍s���Ȃ��悤�ɂ���
								max[i] = j;
								temppoint = tem.cells[(preP[i] + Transform::DirToDelta(Direction(j))).y][(preP[i] + Transform::DirToDelta(Direction(j))).x].point;
								didnewway = true;
							}
	
						}
					}
				}
			}
			if (didnewway == false) {//�œK�ȃ}�X��������Ȃ�������A��O�̃}�X�ɖ߂�
				max[i] = lastMovedBy[i];
			}
			temppoint = 0;
			lastMovedBy[i] = RC::movedByway(max[i]);
			didnewway = false;
		}

		_think = Think{ tem.DecideStepByDirection(preP[0], Direction(max[0])), tem.DecideStepByDirection(preP[1], Direction(max[1])) };

		_is_ready = true;
	}



public:
	RatioClient(TeamType type);
	~RatioClient();
};