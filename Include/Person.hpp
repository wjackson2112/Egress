#ifndef PERSON_HPP
#define PERSON_HPP

#include "Entity.hpp"
#include "Circle.hpp"
#include "Collider.hpp"
#include "IKeyboardEventHandler.hpp"
#include "EventManager.hpp"
#include "Wall.hpp"

class Person : public Entity, public ColliderParent, IKeyboardEventHandler
{
	Uint8 mR, mG, mB;
	SDL_Texture* mBackground;

	EventManager& mEventManager;

	int mVelX, mVelY; // Velocity is pixels per second
	int maxVelX = 100;
	int maxVelY = 100;
	Circle* mColliderShape;
public:
	// Collider* collider;

	Person(int r, int g, int b, Point center, EventManager& eventManager);
	~Person();

	bool render(Camera* camera);
	void update(int frameTime);

	void colliderCallback(ColliderParent *, Shape *);
	void negotiateCollision(ColliderParent *, Shape *);

	void handleKeyboardEvents(const Uint8*);
};

#endif