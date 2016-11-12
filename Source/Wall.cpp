#include "Wall.hpp"

Wall::Wall(int r, int g, int b, Rect rect) : mR{r}, mG{g}, mB{b}
{
	SDL_Rect sdlRect;
	SDL_Surface* surface;

	collider = new Collider((Rect*) this, 100, this);
	setOrigin(rect.origin());
	setSize(rect.size());

	surface = SDL_CreateRGBSurface(0, this->size().x, this->size().y, 32, 0, 0, 0, 0);

	sdlRect = (SDL_Rect) {0, 0, rect.size().x, rect.size().y};
	SDL_FillRect(surface, &sdlRect, SDL_MapRGB(surface->format, mR, mG, mB));
	mBackground = SDL_CreateTextureFromSurface(WindowManager::Instance().renderer, surface);

	SDL_FreeSurface(surface);
}

Wall::~Wall()
{
	delete collider;
	SDL_DestroyTexture(mBackground);
}

bool Wall::render(Camera* camera)
{
	SDL_Rect srcRect, destRect;

	srcRect = (SDL_Rect) {0, 0, size().x, size().y};

	if(camera == NULL)
	{
		destRect = this->toSDLRect();

		SDL_RenderCopy(WindowManager::Instance().renderer, mBackground, &srcRect, &destRect);
	}
	else
	{
		destRect = camera->apply(*this).toSDLRect();

		SDL_RenderCopy(WindowManager::Instance().renderer, mBackground, &srcRect, &destRect);
	}

	return true;
}

void Wall::update(int frameTime)
{

}

void Wall::colliderCallback(ColliderParent *, Shape* shape)
{

}

void Wall::negotiateCollision(ColliderParent *, Shape* shape)
{

}
