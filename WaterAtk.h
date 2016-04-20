#ifndef WATERATK_H
#define WATERATK_H

#include "enemyAtk.h"

class WaterAtk : public enemyAtk{
public:
	WaterAtk();
	WaterAtk(ALLEGRO_BITMAP *waterimage);
};
#endif