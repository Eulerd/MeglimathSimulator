#pragma once
#include "ManualClient.h"
class KeyboardClient :
	public ManualClient
{
private:
	Array<Key> _operation_keys;

protected:
	Optional<Direction> decideDirection() override
	{
		Optional<Direction> dir = none;

		// Right���甽���v���ɕ����L�[���w��
		for (int i : step(9))
		{
			if (_operation_keys[i].down())
			{
				return Optional<Direction>(static_cast<Direction>(i));
			}
		}

		return dir;
	}

public:
	KeyboardClient(Array<Key> operation_keys);
	~KeyboardClient();
};

