#pragma once
#include "Battleship.h"
#include "Game.h"

Battleship::Battleship(Game* game, Owner::Owner owner)
	:mGame{ game }, mOwner{ owner }, mRotation{ 0.0 }, mSpeed{ 0.0f }
{
	mPosition = (owner == Owner::PLAYER_ONE) ? Vector2(60, Game::mWindowHeight / 2) : Vector2(Game::mWindowWidth - 60, Game::mWindowHeight / 2);
	mHeading = (owner == Owner::PLAYER_ONE) ? Vector2(1, 0) : Vector2(-1, 0);
	for (int i = 0; i < HITBOX_MAX; i++)
	{
		HitBox h = HitBox(mHeading * ((i - 2) * 25) + mPosition);
		mHitBoxes[i] = h;
	}

}

void Battleship::UpdateBattleship(float deltaTime)
{
	mPosition = mPosition + mHeading * mSpeed * deltaTime;
	if (mRotation != 0) RotateBattleship();
	WrapAroundPosition(mPosition);
	PositionHitboxes();
	if (mShell != nullptr) mShell->UpdateShell(deltaTime);
}

void Battleship::RemoveShell(Shell* shell)
{
	delete shell;
	mShell = nullptr;
}

void Battleship::WrapAroundPosition(Vector2& loc)
{
	if (loc.x > Game::mWindowWidth) loc.x -= Game::mWindowWidth;
	if (loc.x < 0) loc.x += Game::mWindowWidth;
	if (loc.y > Game::mWindowHeight) loc.y -= Game::mWindowHeight;
	if (loc.y < 0) loc.y += Game::mWindowHeight;
}

void Battleship::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r;
	r.w = 14;
	r.h = 14;
	for (size_t i = 0; i < HITBOX_MAX; i++)
	{
		WrapAroundPosition(mHitBoxes[i].mPosition);
		r.x = mHitBoxes[i].mPosition.x - 7;
		r.y = mHitBoxes[i].mPosition.y - 7;
		if (mHitBoxes[i].mHitStatus == HitBox::HitStatus::HIT) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &r);
		if (mHitBoxes[i].mHitStatus == HitBox::HitStatus::HIT) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	if (mShell != nullptr) mShell->Draw(renderer);
}

void Battleship::RotateBattleship()
{
	mHeading.x = cosf(mRotation) * mHeading.x - sinf(mRotation) * mHeading.y;
	mHeading.y = sinf(mRotation) * mHeading.x + cosf(mRotation) * mHeading.y;
	mHeading.Normalize();
}

void Battleship::PositionHitboxes()
{
	for (int i = 0; i < HITBOX_MAX; i++)
	{
		mHitBoxes[i].mPosition = mHeading * ((i - 2) * 25) + mPosition;
	}

}

void Battleship::Fire(Vector2 direction)
{
	if (SDL_TICKS_PASSED(SDL_GetTicks64(), mLastFiredAt + 3000.0f) && mShell == nullptr)
	{
		mShell = new Shell(this, direction, mPosition, mEnemyHitBoxes);
		mLastFiredAt = SDL_GetTicks64();
	}
}

void Battleship::ProcessKeyInput(const Uint8* state)
{
	if (mOwner == Owner::PLAYER_ONE) ProcessP1Keys(state);
	else ProcessP2Keys(state);
}

void Battleship::ProcessP1Keys(const Uint8* state)
{
	if (mSpeed > mMAX_SPEED) mSpeed = mMAX_SPEED;

	mRotation = 0;

	if (state[SDL_SCANCODE_W])
	{
		mSpeed += 1.0f;
	}
	if (!state[SDL_SCANCODE_W])
	{
		mSpeed -= mSpeed < 0.01f ? 0.0f : 0.5f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRotation -= 0.01f;
	}
	if (state[SDL_SCANCODE_D])
	{
		mRotation += 0.01f;
	}
	if (state[SDL_SCANCODE_Q])
	{
		Fire(Vector2(mHeading.y, -1 * mHeading.x));

	}
	if (state[SDL_SCANCODE_E])
	{
		Fire(Vector2(-1 * mHeading.y, mHeading.x));
	}
}

void Battleship::ProcessP2Keys(const Uint8* state)
{

	if (mSpeed > mMAX_SPEED) mSpeed = mMAX_SPEED;
	if (mSpeed < 0) mSpeed = 0;
	mRotation = 0;

	if (state[SDL_SCANCODE_I])
	{
		mSpeed += 1.0f;
	}
	if (!state[SDL_SCANCODE_I])
	{
		mSpeed -= mSpeed < 0.01f ? 0.0f : 0.5f;
	}
	if (state[SDL_SCANCODE_J])
	{
		mRotation -= 0.01f;
	}
	if (state[SDL_SCANCODE_L])
	{
		mRotation += 0.01f;
	}
	if (state[SDL_SCANCODE_U])
	{
		Fire(Vector2(mHeading.y, -1 * mHeading.x));
	}
	if (state[SDL_SCANCODE_O])
	{
		Fire(Vector2(-1 * mHeading.y, mHeading.x));
	}
}

void Battleship::IncreaseScore()
{
	mScore++;
	if (mScore >= 4) mGame->ClaimVictory(this);
}


