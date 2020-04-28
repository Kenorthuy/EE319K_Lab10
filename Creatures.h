#include <stdint.h>

void landerMove(uint8_t);
void humanMove(void);
void spawnShot(uint8_t, uint8_t, uint8_t);
void moveShot(uint8_t);
void checkHit(uint8_t);
void enemyMove(void);

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
	uint8_t xpos, ypos;
	uint8_t newxpos, newypos;
	uint8_t xvel;
	uint8_t width;
	uint8_t height;
	uint8_t lives;
	uint8_t movingFlag;
	uint8_t facingLeft; //0 is right, 1 is left
	uint8_t thrust;
} player_t;

typedef struct{
	int16_t xpos;
	int16_t ypos;
	uint8_t xvel;
	uint8_t yvel;
	uint8_t override;
} ball_t;

extern uint8_t gameDone;

extern creature_t enemies[2];

extern creature_t humans[1];

extern player_t player[1];

extern ball_t shots[5];
