#pragma once
#include "Vector2.h"
#include <SDL.h>

class Battleship
{
public:
	enum Owner
	{
		PLAYER_ONE,
		PLAYER_TWO
	};

	enum HIT_BOXES
	{
		BACK,
		MIDBACK,
		MIDFRONT,
		FRONT,
		HITBOX_MAX
	};

	Battleship(Owner owner);
	void UpdateBattleship(float deltaTime);
	void ProcessKeyInput(const Uint8* state);
	void draw(SDL_Renderer* renderer);

private:

	void ProcessP1Keys(const Uint8* state);
	void ProcessP2Keys(const Uint8* state);
	void RotateBattleship();
	void PositionHitboxes();
	void WrapAroundPosition(Vector2 &loc);
	

	Vector2 mHeading;
	Vector2 mPosition;
	float mSpeed;
	const float mMAX_SPEED = 75.0f;
	float mRotation;
	Vector2 mHitBoxes[HITBOX_MAX];
	Owner mOwner;
};