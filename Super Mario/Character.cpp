#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	this->mRenderer = renderer;
	this->mTexture = new Texture2D(renderer);
	this->mTexture->LoadFromFile(imagePath);
	this->mPosition = startPosition;
	this->mFacingDirection = RIGHT;
	this->mSpeed = 0.05;
	this->mWalkingFrameCount = 0;
	mSourceRect = new SDL_Rect{0, 32, 16, 27};
	this->walkAnimation = new Animation(renderer, imagePath, mSourceRect, 3, 300);
	mMovingLeft = false;
	mMovingRight = false;
}

Character::~Character()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Character::Render()
{
	switch (mFacingDirection)
	{
		case RIGHT:
		{
			mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 0.0f, mSourceRect);
			break;
		}
		case LEFT:
		{
			mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0f, mSourceRect);
			break;
		}
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_a:
				{
					mMovingLeft = true;
					break;
				}

				case SDLK_d:
				{
					mMovingRight = true;
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
					mMovingLeft = false;
					break;
				}

				case SDLK_d:
				{
					mMovingRight = false;
					break;
				}
			}
			break;
		}
	}
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x -= mSpeed;
	mFacingDirection = LEFT;
	walkAnimation->Play(mPosition, SDL_FLIP_NONE, 0.0f);
	//AnimTick(deltaTime);
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += mSpeed;
	mFacingDirection = RIGHT;
	walkAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL, 0.0f);
	//AnimTick(deltaTime);
}

void Character::AnimTick(float deltaTime)
{
	if (mMovingLeft || mMovingRight)
	{
		if (mWalkingFrameCount >= 500)
		{
			if (mSourceRect->x != 16 * 1)
			{
				mSourceRect->x += 16;
			}
			else
			{
				mSourceRect->x = 0;
			}

			mWalkingFrameCount = 0;
		}
		mWalkingFrameCount++;
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

