#include "stdlib.h"
#include "crtdbg.h"

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <ctime>
#include "mappy_A5.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Wizard.h"
#include "LavaTroll.h"
#include "IceTroll.h"
#include "GreyTroll.h"
#include "Objects.h"
#include "enemyAtk.h"
#include "LavaAtk.h"
#include "WaterAtk.h"
#include "StoneAtk.h"
#include "FireMagic.h"
#include "WaterMagic.h"
#include "EarthMagic.h"
#include "WindMagic.h"
#include "SoulStones.h"
#include "HealthBar.h"
#include "HealPad.h"

enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, R, ONE, TWO, THREE, P};

void updateCam(float *camPos, float x, float y, float pWidth, float pHeight);

int main()
{
	//variables
	bool done = false;
	bool keys[10] = {false, false, false, false, false, false, false, false, false, false};
	float camPos[2] = {0,0};
	float enemies = 30;
	const int maxEnemyAmnt = 1;
	const int soulStoneAmnt = 10;
	bool gameOver = false;


	srand(time(0));

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *wizardImage;
	ALLEGRO_BITMAP *fireImage;
	ALLEGRO_BITMAP *waterImage;
	ALLEGRO_BITMAP *enemyImage[maxEnemyAmnt];
	ALLEGRO_BITMAP *earthImage;
	ALLEGRO_BITMAP *windImage;
	ALLEGRO_BITMAP *enemyAtkImage[maxEnemyAmnt];
	ALLEGRO_BITMAP *soulStoneImage[soulStoneAmnt];
	ALLEGRO_BITMAP *healthImage;
	ALLEGRO_BITMAP *healImage;


	ALLEGRO_SAMPLE *trollHit = NULL;
	ALLEGRO_SAMPLE *plyrHit = NULL;
	ALLEGRO_SAMPLE *soulSound = NULL;
	ALLEGRO_SAMPLE *step = NULL;
	ALLEGRO_SAMPLE *atkSound = NULL;
	ALLEGRO_SAMPLE *healSound = NULL;
	ALLEGRO_SAMPLE *tetris = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance3 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance4 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance5 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance6 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance7 = NULL;

	ALLEGRO_TRANSFORM camera;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(screenWidth, screenHeight);			//create our display object

	if(!display)										//test display object
		return -1;


	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(10);

	trollHit = al_load_sample("bwah.wav");
	plyrHit = al_load_sample("uuh.wav");
	soulSound = al_load_sample("disinter.wav");
	step = al_load_sample("step.wav");
	atkSound = al_load_sample("attack.wav");
	healSound = al_load_sample("heal.wav");
	tetris = al_load_sample("tetris.ogg");

	instance1 = al_create_sample_instance(trollHit);
	instance2 = al_create_sample_instance(plyrHit);
	instance3 = al_create_sample_instance(soulSound);
	instance4 = al_create_sample_instance(step);
	instance5 = al_create_sample_instance(atkSound);
	instance6 = al_create_sample_instance(healSound);
	instance7 = al_create_sample_instance(tetris);

	al_set_sample_instance_gain(instance1, 0.8);
	al_set_sample_instance_gain(instance2, 0.75);
	al_set_sample_instance_gain(instance3, 0.6);
	al_set_sample_instance_length(instance4, 0.5);
	al_set_sample_instance_gain(instance6, 0.75);
	al_set_sample_instance_gain(instance7, 0.2);
	al_set_sample_instance_playmode(instance7, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance3, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance4, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance5, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance6, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance7, al_get_default_mixer());

	ALLEGRO_FONT *font36 = al_load_font("Dorovar_Carolus.ttf", 36, 0);
	ALLEGRO_FONT *font48 = al_load_font("Dorovar_Carolus.ttf", 48, 0);

	if(MapLoad("mapS.fmp", 1))
		return -5;

	Player *plyr;

	wizardImage = al_load_bitmap("wizard.png");
	al_convert_mask_to_alpha(wizardImage, al_map_rgb(105, 74, 46));
	plyr = new Wizard(wizardImage);

	fireImage = al_load_bitmap("firemagic.png");
	al_convert_mask_to_alpha(fireImage, al_map_rgb(215, 33, 33));
	FireMagic fire(fireImage);

	waterImage = al_load_bitmap("watermagic.png");
	al_convert_mask_to_alpha(waterImage, al_map_rgb(64, 111, 255));
	WaterMagic water(waterImage);

	earthImage = al_load_bitmap("earthmagic.png");
	al_convert_mask_to_alpha(earthImage, al_map_rgb(204, 173, 97));
	EarthMagic earth(earthImage);

	windImage = al_load_bitmap("windmagic.png");
	al_convert_mask_to_alpha(windImage, al_map_rgb(107, 124, 123));
	WindMagic wind(windImage);

	healthImage = al_load_bitmap("healthBar.png");
	HealthBar *pHealth;
	pHealth = new HealthBar(healthImage, plyr);

	SoulStones soulStone[soulStoneAmnt];
	for(int i=0; i<soulStoneAmnt; i++){
		soulStoneImage[i] = al_load_bitmap("soulstones.png");
		al_convert_mask_to_alpha(soulStoneImage[i], al_map_rgb(105, 111, 110));
		soulStone[i] = soulStoneImage[i];
	}
	enemyAtk *enemyAttack[maxEnemyAmnt];
	Enemy *enemy[maxEnemyAmnt];
	HealthBar *eHealth[maxEnemyAmnt];
	for(int i=0; i<maxEnemyAmnt; i++){
		if(i%3 == 0){
			enemyImage[i] = al_load_bitmap("lavaTroll.png");
			enemyAtkImage[i] = al_load_bitmap("lavaAtk.png");
			enemy[i] = new LavaTroll(enemyImage[i]);
			enemyAttack[i] = new LavaAtk(enemyAtkImage[i]);
		}
		else if(i%3 == 1){
			enemyImage[i] = al_load_bitmap("iceTroll.png");
			enemyAtkImage[i] = al_load_bitmap("waterAtk.png");
			enemy[i] = new IceTroll(enemyImage[i]);
			enemyAttack[i] = new WaterAtk(enemyAtkImage[i]);
		}
		else{
			enemyImage[i] = al_load_bitmap("greyTroll.png");
			enemyAtkImage[i] = al_load_bitmap("rollstone.png");
			enemy[i] = new GreyTroll(enemyImage[i]);
			enemyAttack[i] = new StoneAtk(enemyAtkImage[i]);
		}
		eHealth[i] = new  HealthBar(healthImage, enemy[i]);
		al_convert_mask_to_alpha(enemyImage[i], al_map_rgb(106, 76, 48));
		al_convert_mask_to_alpha(enemyAtkImage[i], al_map_rgb(97, 68, 43));
	}
	healImage = al_load_bitmap("healpad.bmp");
	al_convert_mask_to_alpha(healImage, al_map_rgb(207, 143, 211));
	HealPad heal(healImage);

	Objects *attack = &wind;

	/*backG = al_load_bitmap("map.fmp");
	al_convert_mask_to_alpha(backG, al_map_rgb(106, 76, 48));*/

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_play_sample_instance(instance7);

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_R:
				if(!keys[R])
					keys[R] = true;
				else
					keys[R] = false;
				break;
			case ALLEGRO_KEY_1:
				attack = &wind;
				break;
			case ALLEGRO_KEY_2:
				if(enemies <= 27)
					attack = &water;
				break;
			case ALLEGRO_KEY_3:
				if(enemies <= 26)
					attack = &fire;
				break;
			case ALLEGRO_KEY_4:
				if(enemies <= 25)
					attack = &earth;
				break;
			case ALLEGRO_KEY_P:
				if(!keys[P])
					keys[P] = true;
				else
					keys[P] = false;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				if(plyr->getCurColumn() > 9 && plyr->getCurColumn() < 17)
				{
					attack->reset();
				}
				break;
				/*case ALLEGRO_KEY_1:
				keys[ONE] = false;
				break;*/
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			if(keys[P])
				for(int i=0; i<9; i++)
					keys[i] = false;
			if(keys[SPACE]){
				if(plyr->hit)
					attack->reset();
				plyr->hit = false;
				plyr->attack();
				attack->startAtk(plyr);
				/*if(attack->live)
				al_play_sample_instance(instance5);*/
			}
			else if(keys[UP] && keys[RIGHT]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(NE);
				else
					plyr->walk(NE);
			}
			else if(keys[UP] && keys[LEFT]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(NW);
				else
					plyr->walk(NW);
			}
			else if(keys[DOWN] && keys[RIGHT]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(SE);
				else
					plyr->walk(SE);
			}
			else if(keys[DOWN] && keys[LEFT]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(SW);
				else
					plyr->walk(SW);
			}
			else if(keys[UP]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(N);
				else
					plyr->walk(N);
			}
			else if(keys[RIGHT]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(E);
				else
					plyr->walk(E);
			}
			else if(keys[DOWN]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(S);
				else
					plyr->walk(S);
			}
			else if(keys[LEFT]){
				plyr->hit = false;
				if(keys[R])
					plyr->run(W);
				else
					plyr->walk(W);
			}
			else
				if(!plyr->hit && !keys[P])
					plyr->stop();
			/*if(keys[R] && (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN]))
			al_play_sample_instance(instance4);*/
			if(!keys[P] && plyr->soulCount != soulStoneAmnt)
			{
				attack->updateObj(plyr);
				for(int i=0; i<soulStoneAmnt; i++){
					soulStone[i].updateObj();
				}
				for(int i=0; i<maxEnemyAmnt; i++){
					if(enemy[i]->live)
					{
						enemy[i]->updateTroll(plyr);
						enemyAttack[i]->startAtk(enemy[i], plyr);
						enemyAttack[i]->updateObj(enemy[i], plyr);
					}
				}
				for(int i=0; i<maxEnemyAmnt; i++){
					if(enemy[i]->getCurColumn() >= 42)
						enemies -= static_cast<float>(1)/static_cast<float>(5);
				}
				if(attack->getCurRow() > 0 && attack->getCurColumn() > 2 && keys[SPACE])
					plyr->stop();
			}
			updateCam(camPos, plyr->x, plyr->y, plyr->frameWidth, plyr->frameHeight);

			al_identity_transform(&camera);
			al_translate_transform(&camera, -camPos[0], -camPos[1]);
			al_use_transform(&camera);

			for(int i=0; i<maxEnemyAmnt; i++){
				attack->collideEnemy(enemy[i]);
				if(enemy[i]->hit)
					al_play_sample_instance(instance1);
			}
			for(int i=0; i<maxEnemyAmnt; i++){
				enemyAttack[i]->collidePlayer(plyr);
				if(plyr->hit && plyr->live)
					al_play_sample_instance(instance2);
			}
			for(int i=0; i<soulStoneAmnt; i++){
				soulStone[i].collidePlayer(plyr);
				if(soulStone[i].hit)
					al_play_sample_instance(instance3);
			}
			heal.collidePlayer(plyr);
			if(heal.hit)
				al_play_sample_instance(instance6);
		}
		/*al_draw_bitmap(backG, screenWidth / 2 - 4224 / 2, screenHeight / 2 - 768 / 2, 0);*/
		/*al_draw_bitmap(backG, 0, 0, 0);*/
		MapDrawBG(0, 0, 0, 0, gameWidth, gameHeight);
		heal.draw();
		for(int i=0; i<soulStoneAmnt; i++)
		{
			soulStone[i].draw();
		}
		for(int i=0; i<maxEnemyAmnt; i++)
		{
			if(enemy[i]->live){
				enemy[i]->draw();
				eHealth[i]->draw(enemy[i]);
				if(enemyAttack[i]->live)
					enemyAttack[i]->draw();
			}
		}
		if(plyr->live)
		{
			if(attack->live && plyr->getCurRow() == 2)
			{
				plyr->draw();
				attack->draw();
			}
			if(attack->live && (plyr->getCurRow() == 0 || plyr->getCurRow() == 4 || plyr->getCurRow() == 5))
			{
				attack->draw();
				plyr->draw();
			}
			else
			{
				plyr->draw();
				if(attack->live)
					attack->draw();
			}
		}
		else
			gameOver = true;
		//al_draw_bitmap(healPad, healPadx, healPady, 0);
		pHealth->draw(plyr);
		/*plyr->health = static_cast<int>(plyr->health);*/
		al_draw_textf(font36, al_map_rgb(255,255,255), camPos[0]+5, camPos[1]+5, 0,
			"Health : %i", plyr->health);
		al_draw_textf(font36, al_map_rgb(255,255,255), camPos[0]+5, camPos[1]+35, 0,
			"Soul Stones Collected : %i / %i", plyr->soulCount, soulStoneAmnt);
		if(enemies <= 27)
		{
			al_draw_text(font36, al_map_rgb(242,251,85), camPos[0]+5, camPos[1]+65, 0,
				"Attack Unlocked :  key2");
		}
		if(enemies <=26)
		{
			al_draw_text(font36, al_map_rgb(242,251,85), camPos[0]+5, camPos[1]+95, 0,
				"Attack Unlocked :  key3");
		}
		if(enemies <= 25)
		{
			al_draw_text(font36, al_map_rgb(242,251,85), camPos[0]+5, camPos[1]+125, 0,
				"Attack Unlocked :  key4");
		}
		if(keys[P])
			al_draw_text(font48, al_map_rgb(255, 255, 255), camPos[0]+screenWidth/2, camPos[1]+screenHeight/3, ALLEGRO_ALIGN_CENTRE, "pause");
		if(plyr->soulCount == soulStoneAmnt)
		{
			for(int i=0; i<maxEnemyAmnt; i++)
				enemy[i]->disintegrate();
			al_draw_text(font48, al_map_rgb(255, 255, 0), camPos[0]+screenWidth/2, camPos[1]+screenHeight/3, ALLEGRO_ALIGN_CENTRE, "WINNER");
		}
		if(gameOver)
			al_draw_text(font48, al_map_rgb(255, 0, 0), camPos[0]+screenWidth/2, camPos[1]+screenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");


		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	MapFreeMem();
	al_destroy_bitmap(wizardImage);
	al_destroy_bitmap(healthImage);
	al_destroy_bitmap(waterImage);
	al_destroy_bitmap(fireImage);
	al_destroy_bitmap(earthImage);
	al_destroy_bitmap(windImage);
	al_destroy_bitmap(healImage);
	al_destroy_sample(trollHit);
	al_destroy_sample(plyrHit);
	al_destroy_sample(soulSound);
	al_destroy_sample(step);
	al_destroy_sample(atkSound);
	al_destroy_sample(healSound);
	al_destroy_sample_instance(instance1);
	al_destroy_sample_instance(instance2);
	al_destroy_sample_instance(instance3);
	al_destroy_sample_instance(instance4);
	al_destroy_sample_instance(instance5);
	al_destroy_sample_instance(instance6);
	for(int i=0; i<soulStoneAmnt; i++)
		al_destroy_bitmap(soulStoneImage[i]);
	for(int i=0; i<maxEnemyAmnt; i++){
		al_destroy_bitmap(enemyImage[i]);
		al_destroy_bitmap(enemyAtkImage[i]);
		delete enemy[i];
		delete eHealth[i];
		delete enemyAttack[i];
	}
	delete plyr;
	delete pHealth;
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);	

	_CrtDumpMemoryLeaks();

	return 0;
}
void updateCam(float *camPos, float x, float y, float pWidth, float pHeight)
{
	camPos[0] = -(screenWidth/2) + (x + pWidth/2);
	camPos[1] = -(screenHeight/2) + (y + pHeight/2);

	if(camPos[0] < 0)
		camPos[0] = 0;
	if(camPos[1] < 0)
		camPos[1] = 0;
}
