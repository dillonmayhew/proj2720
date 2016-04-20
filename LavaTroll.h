#ifndef LAVATROLL_H
#define LAVATROLL_H

#include "Sprite.h"
#include "Enemy.h"

class LavaTroll	 : public Enemy {
public:
	LavaTroll();
	LavaTroll(ALLEGRO_BITMAP *trollImage);

	void disintegrate();
	void pace();
};
#endif