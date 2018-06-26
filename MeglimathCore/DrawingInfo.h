#pragma once
#include <Siv3D.hpp>

class DrawingInfo
{
protected:
	/// <summary>
	/// �Z���������̕`�悷��傫��
	/// </summary>
	static constexpr Size cellSize = Size(32, 32);

	/// <summary>
	/// �t�B�[���h��`�悷��ۂ̍���̍��W
	/// </summary>
	static constexpr Point fieldOrigin = Point(16, 64);

	/// <summary>
	/// �X�e�[�^�X����`�悷��ۂ̍���̍��W
	/// </summary>
	static constexpr Point statOrigin = Point(410, 64);
};
