#pragma once
#include "Shell.h"
#include "Battleship.h"
#include "Game.h"

void Shell::UpdateShell(float deltaTime)
{
	mPosition = mPosition + mHeading * mSpeed * deltaTime;

	EdgeCheck();
	if (!mExploded)
	{
		HitCheck();
	}
}

void Shell::Draw(SDL_Renderer* renderer)
{
	SDL_Rect s;
	s.w = 3;
	s.h = 3;
	s.x = mPosition.x;
	s.y = mPosition.y;

	SDL_RenderFillRect(renderer, &s);
}

void Shell::HitCheck()
{
	for (int i = 0; i < 4; i++)
	{
		if ((mEnemyHitBoxes[i].mPosition - mPosition).SquaredLength() < 50)
		{
			mEnemyHitBoxes[i].mHitStatus = HitBox::HitStatus::HIT;
			mExploded = true;
			mOrigin->RemoveShell(this);
			break;

		}
	}
}

void Shell::EdgeCheck()
{
	if (mPosition.x > Game::mWindowWidth || mPosition.x < 0 || mPosition.y < 0 || mPosition.y > Game::mWindowHeight)
	{
		mExploded = true;
		mOrigin->RemoveShell(this);
	}
}

