#include "Entity.h"
#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int playerNum) 
	: Entity(renderer, imagePath, startPosition)
{
	mPlayerNumber = playerNum;
	mMovementSpeed = 0.05;
	mPlayerState = IDLE;
	mDirectionFacing = RIGHT;
	mSourceRect = new SDL_Rect{ 0, 0, 16, 16 };
	mWalkAnimation = new Animation(renderer, imagePath, mSourceRect, 2, 500);
	mIdleAnimation = new Animation(renderer, imagePath, new SDL_Rect{ 0, 32, 16, 16 }, 2, 5000);
	mSleepAnimation = new Animation(renderer, imagePath, new SDL_Rect{ 0, 16, 16, 16 }, 6, 1000);

	//mSleepAnimation->SetLoopStartSprite(4);
}

Player::~Player()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Player::Render()
{
	switch (mPlayerState)
	{
		case WALK:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}

				case LEFT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_NONE);
					break;
				}
			}
			break;
		}

		case IDLE:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}
				case LEFT:
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_NONE);
					break;
				}
			}
			break;
		}

		case SLEEP:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mSleepAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}
				case LEFT:
				{
					mSleepAnimation->Play(mPosition, SDL_FLIP_NONE);
					break;
				}
			}
			break;
		}
	}
}

void Player::Update(float deltaTime, SDL_Event e)
{
	if (mPosition.y < SCREEN_HEIGHT - SMALLCHARACTERHEIGHT * 3)
	{
		mPosition.y += GRAVITY * deltaTime;
	}
	else
	{
		mCanJump = true;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
		mTimeIdle = 0;
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
		mTimeIdle = 0;
	}
	else
	{
		mPlayerState = IDLE;
		mTimeIdle++;
	}

	if (mTimeIdle > 100000)
	{
		mPlayerState = SLEEP;
	}

	if (mJumping)
	{
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		if (mJumpForce <= 0.0f)
		{
			mJumping = false; 
		}
	}
	
	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				
				case SDLK_a:
				{
					if (mPlayerNumber == 1)
					{
						mMovingLeft = true;
					}
					break;
				}

				case SDLK_d:
				{
					if (mPlayerNumber == 1)
					{
						mMovingRight = true;
					}
					break;
				}

				case SDLK_w:
				{
					if (mPlayerNumber == 1)
					{
						if (mCanJump)
						{

							Jump();
						}
					}
					break;
				}
				
				case SDLK_LEFT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingLeft = true;
					}
					break;
				}

				case SDLK_RIGHT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingRight = true;
					}
					break;
				}
				
				case SDLK_UP:
				{
					if (mPlayerNumber == 2)
					{
						if (mCanJump)
						{
							Jump();
						}
					}
					break;
				}
				
				
			}
			break;
		}

		case SDL_KEYUP:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_a:
				{
					if (mPlayerNumber == 1)
					{
						mMovingLeft = false;
					}
					break;
				}

				case SDLK_d:
				{
					if (mPlayerNumber == 1)
					{
						mMovingRight = false;
					}
					break;
				}
				
				
				case SDLK_LEFT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingLeft = false;
					}
					break;
				}

				case SDLK_RIGHT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingRight = false;
					}
					break;
				}		
			}
			break;
		}
	}
	
}

void Player::MoveLeft(float deltaTime)
{
	mPosition.x -= mMovementSpeed;
	mDirectionFacing = LEFT;
	mPlayerState = WALK;
	//AnimTick(deltaTime);
}

void Player::MoveRight(float deltaTime)
{
	mPosition.x += mMovementSpeed;
	mDirectionFacing = RIGHT;
	mPlayerState = WALK;
	//AnimTick(deltaTime);
}

void Player::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

