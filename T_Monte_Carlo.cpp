#include "T_Monte_Carlo.h"

TileType T_Monte_Carlo::TeamtoTile(TeamType t) {
	switch (t) {
	case TeamType::A:
		return TileType::A;
	case TeamType::B:
		return TileType::B;
	}
}

int T_Monte_Carlo::decideMove(Array<int> *movelist, Agent agent, Field field) {

	int preMove;
	_Point<> preP;
	if ((*movelist).isEmpty()) {
		while (1) {
			//����8�}�X�������_���ɑI��
			preMove = Random(0, 7);
			preP = agent.position + Transform::DirToDelta((Direction(preMove)));
			//�����_���ɑI�񂾃}�X���t�B�[���h�����m�F����B�t�B�[���h�O���������蒼��
			//���`�[���̃^�C���͌������珜�O����悤�ɂ����̂��R�����g�A�E�g����Ă��镔�������A�����K�p����ƂƂ�ł��Ȃ������������Ȃ�
			if (field.IsInField(preP) //&& field.cells[preP.y][preP.x].GetTile() != TeamtoTile(this->_type)
				){
				(*movelist).push_back(preMove);
				return (field.cells[preP.y][preP.x]).point;
			}
		}
	}
	else {
		//����܂œ������}�X���X�g(movelist)�ɂ��铮��L�^�𔽉f�����A���샊�X�g��K�p����Ƃǂ��ɃG�[�W�F���g�����邱�ƂɂȂ�̂��v�Z����
		preP = agent.position;
		for (int i = 0; i < (*movelist).size(); i++) {
			preP += Transform::DirToDelta(Direction((*movelist)[i]));
		}

		while (1) {
			//����8�}�X�������_���ɑI��
			preMove = Random(0, 7);
			//�I�񂾃}�X���t�B�[���h�����m�F����
			//�R�����g�A�E�g�����͎��`�[���̃^�C�����������珜�O������́B�K�p����Ə����������Ȃ�
			if (field.IsInField(preP + Transform::DirToDelta(Direction(preMove)))
				//&& field.cells[preP.y][preP.x].GetTile() != TeamtoTile(this->_type)
				) {
				(*movelist).push_back(preMove);
				return field.cells[preP.y][preP.x].point;
			}
		}
	}
}

void T_Monte_Carlo::sort(Array<std::pair<Array<int>, int>> *target, int left, int right) {
	int i, j, pivot;
	std::pair<Array<int>, int> temp;

	i = left;
	j = right;

	pivot = (*target)[left].second;

	while (1) {
		while ((*target)[i].second < pivot) {

			i++;
		}
	
		while (pivot < (*target)[j].second) {

			j--;

		}

		if (i >= j) {
			break;
		}

		temp = (*target)[i];
		(*target)[i] = (*target)[j];
		(*target)[j] = temp;
		i++;
		j--;
	}

	if (left < i - 1) sort(target, left, i - 1);
	if (j + 1 < right) sort(target, j + 1, right);
}

T_Monte_Carlo::T_Monte_Carlo(TeamType type)
	:Client(type) {

	_is_ready = true;

}

T_Monte_Carlo::~T_Monte_Carlo() {

}