#ifndef ICETROLL_H
#define ICETROLL_H

#include "Sprite.h"
#include "Enemy.h"

class IceTroll: public Enemy {
public:
	IceTroll();
	IceTroll(ALLEGRO_BITMAP *trollImage);
	
	void disintegrate();
	void pace();
};
#endif