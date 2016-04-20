#ifndef STONEATK_H
#define STONEATK_H

#include "enemyAtk.h"

class StoneAtk : public enemyAtk{
public:
	bool imageChange;
	StoneAtk();
	StoneAtk(ALLEGRO_BITMAP *stoneimage);
	void updateObj(Enemy *enemy, Player *plyr);

};
#endif