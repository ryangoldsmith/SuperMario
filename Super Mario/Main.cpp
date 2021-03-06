#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <Windows.h>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

using namespace std;

//Globals
SDL_Window*	gWindow	= NULL;
SDL_Renderer* gRenderer = NULL;

GameScreenManager* gameScreenManager;
Uint32 gOldTime;

Mix_Music* gMusic = NULL;

//Prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();

void SetRandomWindowIcon();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		gOldTime = SDL_GetTicks();

		bool quit = false;

		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();
	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	} 
	else
	{
		gWindow = SDL_CreateWindow("Super Mario Bros",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		SetRandomWindowIcon();

		if (gWindow == NULL)
		{
			cout << "SDL did not initialise. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError() << endl;
				return false;
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				cout << "SDL_Mixer could not initialise. Error: " << Mix_GetError() << endl;
				return false;
			}

			if (TTF_Init() < 0)
			{
				cout << "SDL_ttf could not initialise. Error: " << TTF_GetError() << endl;
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

	}
	return true;
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
		case SDL_QUIT:
		{
			return true;
			break;
		}
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}


void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	delete gameScreenManager;
	gameScreenManager = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void SetRandomWindowIcon()
{
	vector<string> fileNames;
	string directory = "Images/icons/*.*";
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) {
			fileNames.push_back(fileData.cFileName);
		}
	}
	FindClose(hFind);

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, fileNames.size()-1);

	SDL_Surface* pSurface = IMG_Load(("Images/Icons/" + fileNames.at(dist(mt))).c_str());
	if (pSurface != NULL)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		SDL_SetWindowIcon(gWindow, pSurface);
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create surface. Error: " << IMG_GetError() << endl;
	}
	
}