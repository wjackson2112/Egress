#include "Floor.hpp"

Floor::Floor(int r, int g, int b, Size size) : mR{r}, mG{g}, mB{b}
{
	SDL_Rect rect;
	SDL_Surface* surface;

	setSize(size);

	surface = SDL_CreateRGBSurface(0, this->size().x, this->size().y, 32, 0, 0, 0, 0);

	rect = (SDL_Rect) {0, 0, this->size().x, this->size().y};
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, mR, mG, mB));
	mBackground = SDL_CreateTextureFromSurface(WindowManager::Instance().renderer, surface);

	SDL_FreeSurface(surface);
}

Floor::~Floor()
{
	SDL_DestroyTexture(mBackground);
}

bool Floor::render(Camera* camera)
{
	SDL_Rect srcRect = (SDL_Rect) {0, 0, size().x, size().y};
	SDL_Rect destRect = this->toSDLRect();

	SDL_RenderCopy(WindowManager::Instance().renderer, mBackground, &srcRect, &destRect);

	return true;
}

void Floor::update(int frameTime)
{

}
