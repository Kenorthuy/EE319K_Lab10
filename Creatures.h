#ifndef CREATURES_H
#include <stdint.h>

void initCreatures(void);
void spawnLander(void);
void enemyMove(void);
void landerMove(uint8_t index);

typedef struct { 
  uint8_t type;
  uint8_t xpos;     // how long the array is
	uint8_t ypos;     // how long the array is
	uint8_t width;     // how long the array is
	uint8_t height;     // how long the array is
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

extern creature_t enemies[2];

extern creature_t humans[1];

extern player_t player[1];
#endif
