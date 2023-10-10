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

	if (TTF_Init() != 0)
	{
		SDL_Log("SDL_TTF initialization error: %s", TTF_GetError());
		return false;
	}
	return true;
}

void Game::ClaimVictory(Battleship* ship)
{
	mIsRunning = false;
	mWinner = ship;
}

void Game::InitializeBattleships()
{
	mWinner = nullptr;
	Battleship* ship1 = new Battleship(this, Owner::PLAYER_ONE);
	Battleship* ship2 = new Battleship(this, Owner::PLAYER_TWO);
	mShips[Owner::PLAYER_ONE] = ship1;
	mShips[Owner::PLAYER_TWO] = ship2;
}

void Game::RunLoop()
{
	while (mPlayAgain) {
		while (mIsRunning)
		{
			ProcessInput();
			Update();
			GenerateOutput();
		}
		if (mWinner != nullptr) {
			EndGameLoop();
		}
		else mPlayAgain = false;
	}
}

void Game::CheckForQuitEvent()
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
}

void Game::ProcessInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	CheckForQuitEvent();
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

void Game::EndGameLoop()
{

	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool running = true;
	const char* winner = (mWinner->mOwner == Owner::PLAYER_ONE) ? "Player 1 wins! Play again Y/N?" : "Player 2 wins! Play again Y/N?";
	CleanUpBattleships();
	TTF_Font* font = TTF_OpenFont("consola.ttf", 25);
	SDL_Surface* surface = TTF_RenderText_Solid(font, winner, SDL_Color() = { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	DisplayGameEndText(texture, surface);

	while (running)
	{
		CheckForQuitEvent();
		if (state[SDL_SCANCODE_N])
		{
			running = false;
			mPlayAgain = false;
			CleanUpFont(font, surface, texture);
		}

		if (state[SDL_SCANCODE_Y])
		{
			InitializeBattleships();
			running = false;
			mPlayAgain = true;
			mIsRunning = true;
			CleanUpFont(font, surface, texture);
		}
	}
}

void Game::DisplayGameEndText(SDL_Texture* texture, SDL_Surface* surface)
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Rect textRec;
	textRec.w = surface->w;
	textRec.h = surface->h;
	textRec.x = mWindowWidth / 2 - textRec.w / 2;
	textRec.y = mWindowHeight / 2;
	SDL_RenderCopy(mRenderer, texture, NULL, &textRec);
	SDL_RenderPresent(mRenderer);
}

void Game::CleanUpFont(TTF_Font* font, SDL_Surface* surface, SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void Game::CleanUpBattleships()
{
	for (Battleship* ship : mShips)
		delete ship;
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_Quit();
	SDL_Quit();
}