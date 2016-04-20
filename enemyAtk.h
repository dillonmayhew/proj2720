#ifndef ENEMYATK_H
#define ENEMYATK_H

#include "Objects.h"

class enemyAtk : public Objects{
public:
	enemyAtk(){image = 0;}
	enemyAtk(ALLEGRO_BITMAP *atkimage);
	virtual void startAtk(Enemy *enemy, Player *plyr);
	virtual void reset();
	virtual void updateObj(Enemy *enemy, Player *plyr);
	virtual void collidePlayer(Player *plyr);
	virtual void initAtk(Enemy *enemy);
};
#endif