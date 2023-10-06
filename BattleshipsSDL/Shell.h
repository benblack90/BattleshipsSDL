#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Owner.h"
#include "HitBox.h"

class Shell
{
public:
	Shell(Vector2 heading, Vector2 position, HitBox* enemyHitBoxes)
		:mHeading{ heading }, mPosition{ position }, mEnemyHitBoxes{enemyHitBoxes}
	{}


	void UpdateShell(float deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	float mSpeed = 200.0f;
	bool exploded = false;
	Vector2 mPosition;
	Vector2 mHeading;
	HitBox* mEnemyHitBoxes;

};