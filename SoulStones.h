#ifndef SOULSTONES_H
#define SOULDSTOES_H

#include "Objects.h"

class SoulStones : public Objects {
public:
	SoulStones();
	SoulStones(ALLEGRO_BITMAP *soulimage);
	void updateObj();
	void dissapear();
	void collidePlayer(Player *plyr);
	void reset();
};
#endif