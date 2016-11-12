#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <SDL2/SDL.h>
#include "Point.hpp"
#include "Camera.hpp"
#include "Entity.hpp"

class Floor : public Entity
{
	// SDL_Color mBackground;
	Uint8	mR,mG,mB;
	SDL_Texture* mBackground;
public:
	Floor(int r, int g, int b, Size size);
	~Floor();

	bool render(Camera* camera);
	void update(int frameTime);
};

#endif