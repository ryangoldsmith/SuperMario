#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Commons.h"

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	Texture2D(SDL_Renderer* renderer, SDL_Texture* texture);
	~Texture2D();

	bool LoadFromFile(std::string path);
	void Free();

	void Render(Vector2D newPosition, SDL_RendererFlip flip, float renderScale, SDL_Rect* camera, double angle = 0, SDL_Rect* sourceRect = NULL);
	void Render(Vector2D newPosition, SDL_RendererFlip flip, float renderScale, double angle = 0.0f, SDL_Rect* sourceRect = NULL);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	SDL_Texture* GetTexture() { return mTexture; }

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif // !_TEXTURE2D_H
