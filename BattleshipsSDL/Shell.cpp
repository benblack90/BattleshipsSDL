#pragma once
#include "Shell.h"

void Shell::UpdateShell(float deltaTime)
{
	mPosition = mPosition + mHeading * mSpeed * deltaTime;

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