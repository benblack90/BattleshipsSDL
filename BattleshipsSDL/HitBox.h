#pragma once
#include "Vector2.h"

class HitBox
{
public:
	HitBox();
	HitBox(Vector2 position)
		:mPosition {position}
	{
		mHitStatus = HitStatus::NOT_HIT;
	}

	enum class HitStatus
	{
		HIT,
		NOT_HIT
	};

	Vector2 mPosition;
	HitStatus mHitStatus;
};
