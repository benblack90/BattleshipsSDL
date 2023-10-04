#pragma once
#include "Battleship.h"
#include "Game.h"

Battleship::Battleship(Game* game, Owner owner)
	:mOwner{owner}
{
	mPosition = (owner == PLAYER_ONE) ? Vector2(0+10, game->mWindowHeight/2) : Vector2(game->mWindowWidth - 10, game->mWindowHeight/2);
	mHeading = (owner == PLAYER_ONE) ? Vector2(0, 1) : Vector2(0, -1);
}

void Battleship::UpdateBattleship(float deltaTime)
{
	mPosition = mPosition + mHeading * mSpeed * deltaTime;
	if (mRotation != 0) mHeading = RotateBattleship();
}

Vector2 Battleship::RotateBattleship()
{
	mHeading.x = cos(mRotation) * mHeading.x - sin(mRotation) * mHeading.y;
	mHeading.y = sin(mRotation) * mHeading.x + cos(mRotation) * mHeading.y;
}

void Battleship::ProcessKeyInput(const Uint8* state)
{
	if (mOwner == PLAYER_ONE) ProcessP1Keys(state);
	else ProcessP2Keys(state);
}

void Battleship::ProcessP1Keys(const Uint8* state)
{
	mSpeed = 0;
	mRotation = 0;
	if (state[SDL_SCANCODE_W])
	{
		mSpeed += 200.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRotation += 100.0f;
	}
	if (state[SDL_SCANCODE_D])
	{
		mRotation -= 100.0f;
	}
}

void Battleship::ProcessP2Keys(const Uint8* state)
{
	if (state[SDL_SCANCODE_I])
	{
		mSpeed += 200.0f;
	}
	if (state[SDL_SCANCODE_J])
	{
		mRotation += 100.0f;
	}
	if (state[SDL_SCANCODE_L])
	{
		mRotation -= 100.0f;
	}
}


