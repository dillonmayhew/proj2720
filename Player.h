#ifndef PLAYER_H
#define PLAYER_H
//#include "Sprite.h"

class Player : public Sprite {
public:
	void runDirect(DIRECTION D);
	void run(DIRECTION D);
	void beenHit();

	void attack();

	void stop();

};
#endif