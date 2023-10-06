#pragma once
#include "Vector2.h"
#include <SDL.h>
#include "Owner.h"
#include "Shell.h"
#include "HitBox.h"

class Battleship
{
public:
	enum HIT_BOXES
	{
		BACK,
		MIDBACK,
		MIDFRONT,
		FRONT,
		HITBOX_MAX
	};

	Battleship(Owner::Owner owner);
	void UpdateBattleship(float deltaTime);
	void ProcessKeyInput(const Uint8* state);
	void Draw(SDL_Renderer* renderer);
	HitBox* GetHitboxes() { return mHitBoxes; }
	inline void SetEnemyHitBoxes(HitBox* enemyHitBoxes) { mEnemyHitBoxes = enemyHitBoxes; }

private:

	void ProcessP1Keys(const Uint8* state);
	void ProcessP2Keys(const Uint8* state);
	void RotateBattleship();
	void PositionHitboxes();
	void WrapAroundPosition(Vector2 &loc);
	void Fire(Vector2 direction);
	void RemoveShell();
	

	Vector2 mHeading;
	Vector2 mPosition;
	float mSpeed;
	const float mMAX_SPEED = 75.0f;
	float mRotation;
	HitBox mHitBoxes[HITBOX_MAX];
	Owner::Owner mOwner;
	HitBox* mEnemyHitBoxes;
	Shell* mShell;
	float mLastFiredAt;
};