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

typedef struct { 
  uint8_t type;
  uint8_t xpos;
	uint8_t ypos;
	uint8_t width;
	uint8_t height;
} creature_t;

creature_t enemies[2] = {
	{lander, 20, 20, landerw, landerh},
	{lander, 80, 80, landerw, landerh}
};

creature_t humans[2] = {
	{human, 41, 110, humanw, humanh},
	{human, 91, 110, humanw, humanh}
};

void initCreatures() {
}

void spawnLander() {
	//this will probably have to be done in main since
}

void landerMove(uint8_t index) {
	if(humans[index].xpos + humans[index].width/2 < enemies[index].xpos + enemies[index].width/2) {				//try to get the center of the lander to align with the center of the human
		(enemies[index].xpos)--;
	}
	if(humans[index].xpos + humans[index].width/2 > enemies[index].xpos + enemies[index].width/2) {
		(enemies[index].xpos)++;;
	}
	if(humans[index].xpos + humans[index].width/2 == enemies[index].xpos + enemies[index].width/2 && humans[index].ypos > enemies[index].height+humanh) {	//if theyre aligned, start going down
		(enemies[index].ypos)++;
	}
}

void enemyMove() {										//this calls all the enemies to move in their certain way
	for(int i = 0; i < 4; i++) {
		if(enemies[i].type == lander) {
			landerMove(i);
		}
	}
}


