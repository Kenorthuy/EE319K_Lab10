// Creatures.c
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// 1/17/2020
#include <stdint.h>
#include "Random.h"

#define human 0				//defining some values for ease
#define lander 1
#define mutant 2

#define humanh 12
#define humanw 7

#define landerh 12
#define landerw 13

#define mutanth 12
#define mutantw 13

#define playerRh 8
#define playerRw 15

#define screenH 128
#define screenW 128

typedef struct { 
  uint8_t type;
  int16_t xpos;
	int16_t ypos;
	uint8_t width;
	uint8_t height;
	uint8_t dead;				//if an enemy is dead or if a lander leaves with a human, this will allow them to be overwritten
	uint8_t deadimpact;	//property for humans which die if they fall from too high up
	uint8_t pickedup;		//property unique to astronauts for tracking vertical position
	uint8_t carrying;		//property unique to landers for moving humans out
} creature_t;
uint8_t fullEnemy = 0;

typedef struct{
	uint8_t xpos;
	uint8_t ypos;
	uint8_t xvel;
	uint8_t yvel;
	uint8_t width;
	uint8_t height;
	uint8_t lives;
	uint8_t movingFlag;
	uint8_t direction; //0 is right, 1 is left
} player_t;

typedef struct{
	int16_t xpos;
	int16_t ypos;
	uint8_t xvel;			//1 is left, 2 is right
	uint8_t yvel;			//1 is down, 2 is up
	uint8_t override;	//1 means it can be overwritten, 0 means it still exists
} ball_t;
uint8_t fullShot = 0;

player_t player[1] ={
	{10, 10, 0, 0, playerRw, playerRh, 3, 0, 0}
};

creature_t enemies[2] = {
	{lander, 20, 20, landerw, landerh, 0, 0, 0, 0},
	{lander, 80, 80, landerw, landerh, 0, 0, 0, 0}
};

creature_t humans[1] = {
	{human, 41, 110, humanw, humanh, 0, 0, 0, 0}
};

ball_t shots[5] = {											//a maximum of three balls on screen at once
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1}
};

void initCreatures(void);
void spawnLander(void);
void landerMove(uint8_t);
void humanMove(void);
void spawnShot(uint8_t, uint8_t, uint8_t);
void moveShot(uint8_t);

void initCreatures() {
}

void spawnLander() {
	//this will probably have to be done in main
}

void landerMove(uint8_t index) {
	if(humans[0].pickedup != 1) {
		if(humans[0].xpos + humans[0].width/2 < enemies[index].xpos + enemies[index].width/2) {				//try to get the center of the lander to align with the center of the human
			(enemies[index].xpos)--;
		}
		if(humans[0].xpos + humans[0].width/2 > enemies[index].xpos + enemies[index].width/2) {
			(enemies[index].xpos)++;;
		}
		if(humans[0].xpos + humans[0].width/2 == enemies[index].xpos + enemies[index].width/2 && humans[0].ypos > enemies[index].ypos+humanh-3) {	//if theyre aligned, start going down
			(enemies[index].ypos)++;
		}
	}
	if(((humans[0].pickedup == 0 && enemies[index].carrying == 0) || (humans[0].pickedup == 1 && enemies[index].carrying == 1)) 
		&& humans[0].xpos + humans[0].width/2 == enemies[index].xpos + enemies[index].width/2 && humans[0].ypos <= enemies[index].ypos+humanh-3) {	//if theyre aligned, start going down
		(humans[0].pickedup) = 1;
		(enemies[index].carrying) = 1;									//if the ship with a carrying flag is destroyed, the human falls (ypos increases by 2) and should die if he hits the ground—but that needs to be a function of height
		(enemies[index].ypos)--;
	}
	
	if(enemies[index].carrying == 1 && enemies[index].ypos + humanh - 3 <= 0) {
		humans[0].dead = 1;
		enemies[index].dead = 1;
	}
	if(((Random())%20+1) == 20 && fullShot == 0) {
		uint8_t xway = 0;
		uint8_t yway = 0;
		shots[index].yvel = 0;
		if(enemies[index].xpos > player[0].xpos) {
			xway = 1;
		}
		if(enemies[index].xpos < player[0].xpos) {
			xway = 2;
		}
		if(enemies[index].ypos > player[0].ypos) {
			yway = 2;
		}
		if(enemies[index].ypos < player[0].ypos) {
			yway = 1;
		}
		spawnShot(xway, yway, index);				
	}
}

void humanMove(void) {
	if(humans[0].pickedup == 0 && humans[0].ypos < 110) {
		if(humans[0].ypos < 90) {
			humans[0].deadimpact = 1;
		}
		humans[0].ypos++;
	}
	if(humans[0].pickedup == 1) {				//if the human is picked up, decrease his y position to show he's going up
		humans[0].ypos--;
	}
	if(humans[0].ypos == 110) {
		if(humans[0].deadimpact == 1) {
			//they should die. i dont know how to illustrate that clearly for the player
		}
		else{
			uint8_t randommove = Random()%20+1;
			if(randommove >= 11) {
				humans[0].xpos++;
			}
			else{
				humans[0].xpos--;
			}
		}
	}
}

void spawnShot(uint8_t x, uint8_t y, uint8_t index) {
	uint8_t spot;
	for(int i = 0; i < 3; i++) {
		if(shots[i].override == 1) {
			spot = i;
		}
	}
	shots[spot].xpos = enemies[index].xpos;
	shots[spot].ypos = enemies[index].ypos;
	shots[spot].xvel = x;
	shots[spot].yvel = y;
	shots[spot].override = 0;
}

void moveShot(uint8_t index) {
	if(shots[index].xvel == 2) {
		shots[index].xpos += 2;
	}
	if(shots[index].xvel == 1) {
		shots[index].xpos -= 2;
	}
	if(shots[index].yvel == 2) {
		shots[index].ypos -= 2;
	}
	if(shots[index].yvel == 1) {
		shots[index].ypos += 2;
	}
	if(shots[index].xpos >= screenW || shots[index].ypos >= screenH || shots[index].xpos <= -7 || shots[index].ypos <= -7) {
		shots[index].override = 1;
	}
}

void enemyMove() {										//this calls all the enemies to move in their certain way
	fullShot = 1;
	for(int i = 0; i < 5; i++) {
		if(shots[i].override == 1) {
			fullShot = 0;
		}
		if(shots[i].override == 0) {
			moveShot(i);
		}
	}
	for(int i = 0; i < 4; i++) {
		if(enemies[i].type == lander && enemies[i].dead == 0) {
			landerMove(i);
		}
	}
	if(humans[0].dead == 0) {
		humanMove();
	}
}


