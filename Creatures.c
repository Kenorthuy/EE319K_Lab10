// Creatures.c
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// 1/17/2020
#include <stdint.h>
#include "Random.h"
#include "Timer2.h"
#include "SysTick.h"

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

//this structure keeps track of all non-player creature properties. if a creature does not use a certain value, it wont be checked but its best to leave it at zero to avoid confusion
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

//this structure keeps track of player information
typedef struct{
	uint8_t xpos;
	uint8_t ypos;
	uint8_t newxpos;
	uint8_t newypos;
	uint8_t xvel;
	uint8_t width;
	uint8_t height;
	uint8_t lives;
	uint8_t movingFlag;
	uint8_t facingLeft; //0 is right, 1 is left
	uint8_t thrust;
} player_t;
uint8_t gameDone = 0;			//this flag stores whether the player is dead

//this structure keeps track of projectile information
typedef struct{
	int16_t xpos;
	int16_t ypos;
	uint8_t xvel;			//1 is left, 2 is right
	uint8_t yvel;			//1 is down, 2 is up
	uint8_t override;	//1 means it can be overwritten, 0 means it still exists
	uint8_t enemyOrPlayer; //1 means its player 0 means its enemy
} ball_t;
uint8_t fullShot = 0;
uint8_t fullLaser = 0;

player_t player[1] ={
	{10, 10, 0, 0, 2, playerRw, playerRh, 3, 0, 1, 0}
};

creature_t enemies[2] = {
	{lander, 20, 20, landerw, landerh, 0, 0, 0, 0},
	{lander, 80, 80, landerw, landerh, 0, 0, 0, 0}
};

creature_t humans[1] = {
	{human, 41, 110, humanw, humanh, 0, 0, 0, 0}
};

ball_t shots[5] = {											//a maximum of five balls on screen at once
	{0, 0, 0, 0, 1, 0},											//every value is initialized with 1 in the override field to show that the balls dont exist
	{0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0}
};

ball_t lasers[10] = {											//a maximum of 15 balls on screen at once
	{0, 0, 0, 0, 1, 1},											//every value is initialized with 1 in the override field to show that the balls dont exist
	{0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 1, 1},											//every value is initialized with 1 in the override field to show that the balls dont exist
	{0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1}
};

void landerMove(uint8_t);
void humanMove(void);
void spawnShot(uint8_t, uint8_t, uint8_t);
void spawnPlayerShot(void);
void moveShot(uint8_t);
void movePlayerShot(uint8_t);
void checkHit(uint8_t);
void checkPlayerHit(uint8_t);
void enemyMove(void);

// *************** landerMove *******************************************
// If a human exists on the screen and isn't picked up, the lander should try to reach and pick it up in a predictable manner
// If a lander is carrying a human to the top of the screen, that should be their sole focus
// If another lander is carrying the human or if there is no human this round, landers should move away and attack from a distance (not implemented)
// Landers can fire in 8 directions depending on what is closest to the player
// Input: Index Position of the Enemy
// Output: None
void landerMove(uint8_t index) {
	if(humans[0].pickedup != 1) {																																		//if the human can be picked up
		if(humans[0].xpos + humans[0].width/2 < enemies[index].xpos + enemies[index].width/2) {				//try to get the center of the lander to align with the center of the human
			(enemies[index].xpos)--;
		}
		if(humans[0].xpos + humans[0].width/2 > enemies[index].xpos + enemies[index].width/2) {
			(enemies[index].xpos)++;;
		}
		if(humans[0].xpos + humans[0].width/2 == enemies[index].xpos + enemies[index].width/2 && humans[0].ypos > enemies[index].ypos+humanh-3) {	//if theyre aligned, start going down
			(enemies[index].ypos)++;
		}
	}																																																//if the human is picked up by the lander OR if the human isnt picked up and the lander can get him
	if(((humans[0].pickedup == 0 && enemies[index].carrying == 0) || (humans[0].pickedup == 1 && enemies[index].carrying == 1)) 
		&& humans[0].xpos + humans[0].width/2 == enemies[index].xpos + enemies[index].width/2 && humans[0].ypos <= enemies[index].ypos+humanh-3) {	//if theyre aligned, start going down
		(humans[0].pickedup) = 1;
		(enemies[index].carrying) = 1;									//if the ship with a carrying flag is destroyed, the human falls (ypos increases by 2) and should die if he hits the ground
		(enemies[index].ypos)--;
	}
	
	if(enemies[index].carrying == 1 && enemies[index].ypos + humanh - 3 <= 0) {											//if the human is carried off it and the lander are technically dead
		humans[0].dead = 1;
		enemies[index].dead = 1;
	}
	if(((Random())%20+1) == 20 && fullShot == 0) {																									//the lander can decide randomly to shoot in the players general direction
		uint8_t xway = 0;
		uint8_t yway = 0;
		shots[index].yvel = 0;
		if(enemies[index].xpos > player[0].xpos) {																										//the lander picks a direction for projectile velocity here
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

// *************** humanMove ********************************************
// The human runs around the x direction in a panic unless hes picked up or drops
// Input: None
// Output: None
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
			humans[0].dead = 1;
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
	if(humans[0].xpos + humans[0].width >= player[0].xpos && humans[0].xpos <= player[0].xpos + player[0].width && 
		 humans[0].ypos + humans[0].height>= player[0].ypos && humans[0].ypos <= player[0].ypos + player[0].height) {
			 humans[0].deadimpact = 0;
	}
}

// *************** spawnShot ********************************************
// This creates a shot object that is given the position of the shooter and the appropriate x and y velocities. it also clears the override flag, which makes it drawable
// Input: x = x velocity; y = y velocity; index = index position of the enemy in enemies[]
// Output: None
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

void spawnPlayerShot() {
	if(makeShot == 1) {
		uint8_t spot;
		for(int i = 0; i < 10; i++) {
			if(lasers[i].override == 1) {
				spot = i;
			}
		}
		lasers[spot].xpos = player[0].xpos;
		lasers[spot].ypos = player[0].ypos;
		if(player[0].facingLeft) {
			lasers[spot].xvel = 0;
		}
		else {
			lasers[spot].xvel = 1;
		}
		lasers[spot].yvel = 0;
		lasers[spot].override = 0;
		
		makeShot = 0;
	}
}


// *************** moveShot *********************************************
// Updates shot position according to velocity information. If the shot hits the edge of the screen, it is no longer drawn
// Input: Index position of the shot within shots[]
// Output: None
void moveShot(uint8_t index) {
	checkHit(index);
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
		shots[index].override = 1;						//set override if the projectile hits any screen edges
	}
}

void movePlayerShot(uint8_t index) {
	checkPlayerHit(index);
	if(lasers[index].xvel == 1) {
		lasers[index].xpos += 2;
	}
	else {
		lasers[index].xpos -= 2;
	}
	if(lasers[index].xpos >= screenW || lasers[index].xpos <= -7) {
		lasers[index].override = 1;						//set override if the projectile hits any screen edges
	}
}

// *************** checkHit *********************************************
// compares shot position information to player position information. if the x and y information align, a life is taken and a small animation should play. 
// if the player has no lives, immediately raise the game over flag
// Input: Index position of the shot within shots[]
// Output: None
void checkHit(uint8_t thisShot) {
	if(shots[thisShot].xpos >= player[0].xpos && shots[thisShot].xpos <= player[0].xpos + playerRw - 4 && shots[thisShot].ypos >= player[0].ypos && shots[thisShot].ypos <= player[0].ypos + playerRh-4) {
		player[0].lives--;								//the player does not exist
		shots[thisShot].override = 1;			//the shot does not exist
	}
	if(player[0].lives == 0) {
		gameDone = 1;
	}
}

void checkPlayerHit(uint8_t thisShot) {
	for(int i = 0; i < 2; i++) {
		if(lasers[thisShot].xpos + 12>= enemies[i].xpos && lasers[thisShot].xpos <= enemies[i].xpos + enemies[i].width&& 
			 lasers[thisShot].ypos + 2>= enemies[i].ypos && lasers[thisShot].ypos <= enemies[i].ypos + enemies[i].height) {
			enemies[i].dead = 1;
			lasers[thisShot].override = 1;
			break;
		}
	}
}

// *************** enemyMove ********************************************
// moves enemies, humans, and projectiles in their proper way
// Input: None
// Output: None
void enemyMove() {										//this calls all the enemies to move in their certain way
	fullShot = 1;
	fullLaser = 1;
	for(int i = 0; i < 5; i++) {
		if(shots[i].override == 1) {			//fullShot is how enemies are aware if there are too many projectiles on screen
			fullShot = 0;
		}
		if(shots[i].override == 0) {			//if a shot exists, it should be moved until it doesnt
			moveShot(i);
		}
	}
	spawnPlayerShot();
	for(int i = 0; i < 10; i++) {
		if(lasers[i].override == 1) {			//fullShot is how enemies are aware if there are too many projectiles on screen
			fullLaser = 0;
		}
		if(lasers[i].override == 0) {			//if a shot exists, it should be moved until it doesnt
			movePlayerShot(i);
		}
	}
	for(int i = 0; i < 4; i++) {
		if(enemies[i].type == lander && enemies[i].dead == 0) {
			landerMove(i);									//a non-dead enemy should move
		}
		if(enemies[i].dead == 1 && enemies[i].carrying == 1) {
			humans[0].pickedup = 0;
		}
		if(enemies[i].dead == 1 && changeFrame) {
			enemies[i].dead = 2;						//now this should make them overwritable later
		}
	}
	if(humans[0].dead == 0) {
		humanMove();											//a non-dead human should move
	}
}


