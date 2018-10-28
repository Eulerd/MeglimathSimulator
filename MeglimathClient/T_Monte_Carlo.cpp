﻿#include "T_Monte_Carlo.h"

int T_Monte_Carlo::decideMove(Array<int> *movelist, _Point<> preP, Field field) {

	int preMove;
	//_Point<> preP;

	bool okflag = false;
	int temp;

	Array<int> candinate = { 0,1,2,3,4,5,6,7 };

	while (1) {
		//周囲8マスをランダムに選ぶ
		if (candinate.isEmpty()) {
			preMove = Random(0, 7);
			if (field.IsInField(preP + Transform::DirToDelta(Direction(preMove)))) {
				okflag = true;
			}
		}
		else {
			temp = candinate.count() - 1;
			preMove = candinate[Random(0, temp)];
			auto select_pos = preP + Transform::DirToDelta(Direction(preMove));
			if (field.IsInField(select_pos)) {
				if (field.cells[select_pos].tile != Transform::ToTile(type)) {
					okflag = true;
				}
			}
		}

		//preP = agent.position + Transform::DirToDelta((Direction(preMove)));
		//ランダムに選んだマスがフィールド内か確認する。フィールド外だったらやり直し
		//自チームのタイルは検索から除外するようにしたのがコメントアウトされている部分だが、これを適用するととんでもなく処理が長くなる
		if (okflag == true) {
			(*movelist).push_back(preMove);
			preP += Transform::DirToDelta(Direction(preMove));
			return (field.cells[preP]).point;
		}

		candinate.remove(preMove);

	}
	//else {
	//	//これまで動いたマスリスト(movelist)にある動作記録を反映させ、動作リストを適用するとどこにエージェントがいることになるのか計算する
	//	preP = agent.position;
	//	for (int i = 0; i < (*movelist).size(); i++) {
	//		preP += Transform::DirToDelta(Direction((*movelist)[i]));
	//	}

	//	while (1) {
	//		//周囲8マスをランダムに選ぶ
	//		preMove = Random(0, 7);
	//		//選んだマスがフィールド内か確認する
	//		//コメントアウト部分は自チームのタイルを検索から除外するもの。適用すると処理が長くなる
	//		if (field.IsInField(preP + Transform::DirToDelta(Direction(preMove)))
	//			//&& field.cells[preP.y][preP.x].GetTile() != TeamtoTile(this->_type)
	//			) {
	//			(*movelist).push_back(preMove);
	//			return field.cells[preP.y][preP.x].point;
	//		}
	//	}
	//}
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
