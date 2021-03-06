#include "Texture2D.h"

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	this->mRenderer = renderer;
}

Texture2D::Texture2D(SDL_Renderer* renderer, SDL_Texture* texture)
{
	this->mRenderer = renderer;
	this->mTexture = texture;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();

	mTexture = NULL;

	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else
		{
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create surface. Error: " << IMG_GetError() << " " << path << endl;
	}

	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, float renderScale, SDL_Rect* camera, double angle, SDL_Rect* sourceRect)
{
	SDL_Rect renderLocation;
	sourceRect != NULL ? renderLocation = {(int)newPosition.x - camera->x, (int)newPosition.y, (int)(sourceRect->w * renderScale), (int)(sourceRect->h * renderScale)} : renderLocation = { (int)newPosition.x - camera->x, (int)newPosition.y, mWidth, mHeight};

	SDL_RenderCopyEx(mRenderer, mTexture, sourceRect, &renderLocation, angle, NULL, flip);
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, float renderScale, double angle, SDL_Rect* sourceRect)
{
	SDL_Rect renderLocation;
	sourceRect != NULL ? renderLocation = { (int)newPosition.x, (int)newPosition.y, (int)(sourceRect->w * renderScale), (int)(sourceRect->h * renderScale) } : renderLocation = { (int)newPosition.x, (int)newPosition.y,(int)(mWidth * renderScale), (int)(mHeight * renderScale) };

	SDL_RenderCopyEx(mRenderer, mTexture, sourceRect, &renderLocation, angle, NULL, flip);
}


