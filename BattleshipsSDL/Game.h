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

	const int mWindowWidth = 1024;
	const int mWindowHeight = 758;

private:
	void ProcessInput();
	void Update();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	class Battleship* mShips[];
};