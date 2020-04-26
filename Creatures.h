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
} creature_t;

extern creature_t enemies[1];

extern creature_t humans[1];
