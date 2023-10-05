#pragma once
#include <SDL.h>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
	bool InitializeSDL();
	void InitializeBattleships();

	static const int mWindowWidth = 1024;
	static const int mWindowHeight = 758;

private:
	void ProcessInput();
	void Update();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mTicks;
	class Battleship* mShips[2];
};