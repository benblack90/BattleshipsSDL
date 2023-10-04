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

	Battleship(class Game* game, Owner owner);
	void UpdateBattleship(float deltaTime);
	void ProcessKeyInput(const Uint8* state);
	


private:

	void ProcessP1Keys(const Uint8* state);
	void ProcessP2Keys(const Uint8* state);
	Vector2 RotateBattleship();

	Vector2 mHeading;
	Vector2 mPosition;
	float mSpeed;
	float mRotation;
	Owner mOwner;
};