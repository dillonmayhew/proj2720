#ifndef GREYTROLL_H
#define GREYTROLL_H

#include "Sprite.h"
#include "Enemy.h"

class GreyTroll: public Enemy {
public:
	GreyTroll();
	GreyTroll(ALLEGRO_BITMAP *trollImage);
	
	void disintegrate();
	void pace();
};
#endif