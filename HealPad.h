#ifndef HEALPAD_H
#define HEALPAD_H

#include "Objects.h"

class HealPad : public Objects{
public:
	HealPad(ALLEGRO_BITMAP *healimage);
	void collidePlayer(Player *plyr);
};
#endif