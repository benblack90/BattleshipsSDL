#pragma once
#include <SDL.h>
#include "Owner.h"
#include <SDL_ttf.h>

class Game
{
public:
	Game();
	bool Initialize();
	void ClaimVictory(class Battleship* ship);
	void RunLoop();
	void Shutdown();
	bool InitializeSDL();
	void InitializeBattleships();
	void EndGameLoop();

	static const int mWindowWidth = 1024;
	static const int mWindowHeight = 758;

private:
	void ProcessInput();
	void Update();
	void GenerateOutput();
	void CheckForQuitEvent();
	void CleanUpBattleships();
	void CleanUpFont(TTF_Font* font, SDL_Surface* surface, SDL_Texture* texture);
	void DisplayGameEndText(SDL_Texture* texture, SDL_Surface* surface);
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	bool mPlayAgain = true;
	Uint32 mTicks;
	class Battleship* mShips[Owner::PLAYER_MAX];
	class Battleship* mWinner = nullptr;
};