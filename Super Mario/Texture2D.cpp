#include "Texture2D.h"


using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	this->mRenderer = renderer;
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
		cout << "Unable to create surface. Error: " << IMG_GetError() << endl;
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

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	SDL_Rect renderLocation = { 0, 0, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(mRenderer);
}
