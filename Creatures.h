#include <stdint.h>

void initCreatures(void);
void spawnLander(void);
void enemyMove(void);
void landerMove(uint8_t index);

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
	uint8_t xvel;
	uint8_t yvel;
	uint8_t override;
} ball_t;

extern creature_t enemies[2];

extern creature_t humans[1];

extern player_t player[1];

extern ball_t shots[5];
