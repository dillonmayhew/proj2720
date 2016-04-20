#ifndef LAVAATK_H
#define LAVAATK_H

#include "enemyAtk.h"

class LavaAtk : public enemyAtk{
public:
	LavaAtk();
	LavaAtk(ALLEGRO_BITMAP *lavaimage);
};
#endif