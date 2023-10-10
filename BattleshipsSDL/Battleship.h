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

	Battleship(class Game* game, Owner::Owner owner);
	~Battleship();
	void UpdateBattleship(float deltaTime);
	void ProcessKeyInput(const Uint8* state);
	void Draw(SDL_Renderer* renderer);
	HitBox* GetHitboxes() { return mHitBoxes; }
	void RemoveShell(Shell* shell);
	inline void SetEnemyHitBoxes(HitBox* enemyHitBoxes) { mEnemyHitBoxes = enemyHitBoxes; }
	void IncreaseScore();

	Owner::Owner mOwner;

private:

	void ProcessP1Keys(const Uint8* state);
	void ProcessP2Keys(const Uint8* state);
	void RotateBattleship();
	void PositionHitboxes();
	void WrapAroundPosition(Vector2 &loc);
	void Fire(Vector2 direction);
	
	class Game* mGame;
	Vector2 mHeading;
	Vector2 mPosition;
	float mSpeed;
	const float mMAX_SPEED = 100.0f;
	float mRotation;
	HitBox mHitBoxes[HITBOX_MAX];
	
	HitBox* mEnemyHitBoxes;
	Shell* mShell;
	float mLastFiredAt;
	int mScore = 0;
	
};