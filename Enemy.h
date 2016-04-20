#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "Player.h"

enum ENEMY{LAVATROLL, ICETROLL, GREYTROLL};

class Enemy : public Sprite {
public:
	//Enemy(){image = NULL;}
	int xDirect;
	int yDirect;
	int dBound;
	ENEMY ID;
	Enemy(){}
	bool isClose(Player *plyr);
	void moveTowards(Player *plyr);
	bool inAtkDist(Player *plyr);
	void facePlyr(Player *plyr);
	void attack(Player *plyr);
	void stop();
	virtual void pace(){}
	virtual void disintegrate(){}
	void updateTroll(Player *plyr);
	void beenHit();
};
#endif