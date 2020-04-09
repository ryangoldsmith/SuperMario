#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Player.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Constants.h"
#include "MapLoader.h"
#include "Text.h"
#include "Coin.h"
#include "Enemy.h"
//#include "Character.h"

class Texture2D;
//class Entity;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, int numOfPlayers);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	Texture2D* mMarioFace;
	Texture2D* mLuigiFace;
	Vector2D mBackgroundPosition;
	SDL_Rect* mCamera;
	//Player* mPlayers[MAXPLAYERCOUNT];
	Text* mScoreText;
	Text* mDebugText;
	Text* mDeathScreenText;

	std::vector<Player*> mPlayers;
	std::vector<Pipe*> mPipes;
	std::vector<Brick*> mBricks;
	std::vector<Coin*> mCoins;
	std::vector<Enemy*> mEnemys;

	int mPlayerCount,
		mScore,
		mCoinsCollected,
		mMapTileWidth,
		mLives;

	bool mResetingLevel;

	bool SetUpLevel(int numOfPlayers);
	void ResetLevel();

	void Debug();
	void BrickCollisionsWithPlayer(Player* player, bool& botCollided);
	void PipeCollisionsWithPlayer(Player* player, bool& botCollided);
	void CoinCollisionsWithPlayer(Player* player);
	void EnemyCollisionsWithPlayer(Player* player);
	void EnemyCollisionsWithBlocks(Enemy* enemy);
	void RemoveDestroyedBricks(Brick* brick, int brickNum);
	void RemoveDeadEnemies(Enemy* enemy, int enemyNum);
	void SpawnedItemSolidBlockCollisions(PowerUp* powerup);
	void CameraMovementLogic();

	//debug:
	int mDebugType = 0;
	bool debug = false;
	bool f3Down = false, kp2Down = false;
	bool topHit;
};

#endif // !_GAMESCREENLEVEL1_H

