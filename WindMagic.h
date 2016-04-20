#ifndef WINDMAGIC_H
#define WINDMAGIC_H

#include "Objects.h"

class WindMagic : public Objects {
public:
	WindMagic(ALLEGRO_BITMAP *windimage);
	void startAtk(Player *plyr);
};
#endif