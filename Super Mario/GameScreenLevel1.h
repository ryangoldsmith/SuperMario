#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"

class Texture2D;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	Character* character;

	bool SetUpLevel();
};

#endif // !_GAMESCREENLEVEL1_H

