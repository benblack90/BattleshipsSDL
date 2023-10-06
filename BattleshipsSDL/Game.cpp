#include "Game.h"
#include "Battleship.h"

Game::Game()
	:mWindow(nullptr), mRenderer(nullptr), mIsRunning(true)
{}

bool Game::Initialize()
{
	if (!InitializeSDL()) return false;
	else InitializeBattleships();
	return true;
}

bool Game::InitializeSDL()
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("SDL initialization error: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Battleships", 100, 100, mWindowWidth, mWindowHeight, 0);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Error creating renderer: %s", SDL_GetError());
		return false;
	}
	return true;
}

void Game::InitializeBattleships()
{
	Battleship* ship1 = new Battleship(Owner::PLAYER_ONE);
	Battleship* ship2 = new Battleship(Owner::PLAYER_TWO);
	mShips[Owner::PLAYER_ONE] = ship1;
	mShips[Owner::PLAYER_TWO] = ship2;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (Battleship* bp : mShips)
	{
		bp->ProcessKeyInput(state);
	}
}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks64(), mTicks + 16));

	float deltaTime = (SDL_GetTicks64() - mTicks) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicks = SDL_GetTicks64();


	for (int i = 0; i < Owner::PLAYER_MAX; i++)
	{
		int enemy = Owner::PLAYER_MAX - i - 1;
		mShips[i]->UpdateBattleship(deltaTime);
		mShips[i]->SetEnemyHitBoxes(mShips[enemy]->GetHitboxes());
	}	
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	for (Battleship* bp : mShips)
	{
		bp->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}