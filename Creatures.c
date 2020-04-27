// Creatures.c
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// 1/17/2020
#include <stdint.h>

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

typedef struct { 
  uint8_t type;
  uint8_t xpos;
	uint8_t ypos;
	uint8_t width;
	uint8_t height;
	uint8_t pickedup;		//property unique to astronauts for tracking vertical position
	uint8_t carrying;		//property unique to landers for moving humans out
} creature_t;

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

player_t player[1] ={
	{10, 10, 0, 0, playerRw, playerRh, 3, 0, 0}
};

creature_t enemies[2] = {
	{lander, 20, 20, landerw, landerh, 0, 0},
	{lander, 80, 80, landerw, landerh, 0, 0}
};

creature_t humans[1] = {
	{human, 41, 110, humanw, humanh, 0, 0}
};

void initCreatures() {
}

void spawnLander() {
	//this will probably have to be done in main since
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
		(enemies[index].carrying) = 1;									//if the ship with a carrying flag is destroyed, the human falls (ypos increases by 2) and should die if he hits the ground�but that needs to be a function of height
		(enemies[index].ypos)--;
	}
	//there should also be commands for attacking the player if the human is picked up
}

void enemyMove() {										//this calls all the enemies to move in their certain way
	for(int i = 0; i < 4; i++) {
		if(enemies[i].type == lander) {
			landerMove(i);
		}
	}
	if(humans[0].pickedup == 1) {				//if the human is picked up, decrease his y position to show he's going up
		humans[0].ypos--;
	}
}
