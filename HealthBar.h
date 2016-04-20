#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Sprite.h"

class HealthBar : public Sprite {
public:
	HealthBar();
	HealthBar(ALLEGRO_BITMAP *barimage, Sprite *sprite);
	void draw(Sprite *sprite);


};
#endif