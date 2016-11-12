#ifndef WALL_HPP
#define WALL_HPP

#include "Entity.hpp"
#include "Collider.hpp"

class Wall : public Entity, public ColliderParent
{
	Uint8 mR, mG, mB;
	SDL_Texture* mBackground;

public:
	// Collider* collider;

	Wall(int r, int g, int b, Rect rect);
	~Wall();

	bool render(Camera* camera);
	void update(int frameTime);

	void colliderCallback(ColliderParent *, Shape *);
	void negotiateCollision(ColliderParent *, Shape *);
};

#endif