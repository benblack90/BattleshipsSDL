#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "HitBox.h"

class Shell
{
public:
	Shell(class Battleship* origin, Vector2 heading, Vector2 position, HitBox* enemyHitBoxes)
		:mOrigin{origin}, mHeading{ heading }, mPosition{ position }, mEnemyHitBoxes{enemyHitBoxes} 
	{}


	void UpdateShell(float deltaTime);
	void Draw(SDL_Renderer* renderer);
	

private:
	void HitCheck();
	void EdgeCheck();

	float mSpeed = 400.0f;
	bool mExploded = false;
	class Battleship* mOrigin;
	Vector2 mPosition;
	Vector2 mHeading;
	HitBox* mEnemyHitBoxes;

};