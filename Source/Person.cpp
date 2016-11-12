#include "Person.hpp"
#include <iostream>

Person::Person(int r, int g, int b, Point center, EventManager& eventManager) : mR{r}, mG{g}, mB{b},
	mVelX{0}, mVelY{0},
	mEventManager{eventManager}
{
	SDL_Rect rect;
	SDL_Surface* surface;

	eventManager.registerKeyboardEventHandler(this);

	setCenter(center);
	setSize(Size(50, 50));
	mColliderShape = new Circle(this->center(), this->size().x/2);
	collider = new Collider(mColliderShape, 50, this);

	surface = SDL_CreateRGBSurface(0, this->size().x, this->size().y, 32, 0, 0, 0, 0);

	rect = (SDL_Rect) {0, 0, this->size().x, this->size().y};
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, mR, mG, mB));
	mBackground = SDL_CreateTextureFromSurface(WindowManager::Instance().renderer, surface);

	SDL_FreeSurface(surface);
}

Person::~Person()
{
	delete mColliderShape;
	delete collider;
	SDL_DestroyTexture(mBackground);
}

bool Person::render(Camera* camera)
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

void Person::update(int frameTime) //frameTime is in microseconds
{
	setOrigin(Point(frameTime/1000000.0 * mVelX + origin().x, frameTime/1000000.0 * mVelY + origin().y));
	mColliderShape->setCenter(center());
}

void Person::colliderCallback(ColliderParent* parent, Shape* shape)
{
	if(dynamic_cast<Wall*>(parent))
	{
		Rect* wallRect = (Rect*) shape;

		if(mVelX > 0)
		{
			setOrigin(Point(wallRect->origin().x - size().x, origin().y));
		}
		else if(mVelX < 0)
		{
			setOrigin(Point(wallRect->origin().x + wallRect->size().x, origin().y));
		}

		if(mVelY > 0)
		{
			setOrigin(Point(origin().x, wallRect->origin().y - size().y - 1));
		}
		else if(mVelY < 0)
		{
			setOrigin(Point(origin().x, wallRect->origin().y + wallRect->size().y));
		}
	}
}

void Person::negotiateCollision(ColliderParent *, Shape* shape)
{

}

void Person::handleKeyboardEvents(const Uint8* events)
{
	if(events[SDL_SCANCODE_UP])
	{
		mVelY = -maxVelY;
	}
	else if(events[SDL_SCANCODE_DOWN])
	{
		mVelY = maxVelY;
	}
	else
	{
		mVelY = 0;
	}

	if(events[SDL_SCANCODE_LEFT])
	{
		mVelX = -maxVelX;
	}
	else if(events[SDL_SCANCODE_RIGHT])
	{
		mVelX = maxVelX;
	}
	else
	{
		mVelX = 0;
	}
}