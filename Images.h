// images.h
// contains image buffers for simple space invaders
// Jonathan Valvano, 1/17/2020
// Capture image dimensions from BMP files

#ifndef __images_h
#define __images_h
#include <stdint.h>


// *************************** Images ***************************
// enemy ship that spawns at the top of the screen
// finds the x coordinate of the human and goes to pick them up
// width=13 x height=12
const unsigned short landerSprite[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x05C0, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0xFD61, 0x05C0, 0xFD61, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x05C0, 0x0000, 0x05C0, 0x05C0, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x05C0, 0x0000, 0x05C0, 0x05C0, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFD61, 0xFD61, 0xFD61, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFD61, 0xFD61, 0xFD61, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// if the player shoots a lander this shows up for a second or so
// width=13 x height=12
const unsigned short deadLanderSprite[] = {
 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0xE923, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE923, 0xE923, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE923, 0xFD61, 0xE923, 0xE923, 0xE923, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFD61, 0xFD61, 0xFF80, 0xFD61, 0xE923, 0xE923, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xE923, 0xE923, 0xFF80, 0xFF80, 0xE923, 0xE923, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x05C0, 0xFD61, 0xE923, 0xFD61, 0xE923, 0xFD61, 0x0000, 0x0000, 0x05C0, 0x0000, 0x05C0,
 0x0000, 0x05C0, 0x05C0, 0x0000, 0x0000, 0xE923, 0xE923, 0x0000, 0x0000, 0x0000, 0x05C0, 0xFD61, 0x05C0,
 0x0000, 0x05C0, 0x05C0, 0x0000, 0x0000, 0xE923, 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0x05C0, 0x0000,
 0x0000, 0x0000, 0x05C0, 0xFD61, 0x0000, 0x0000, 0x0000, 0xFD61, 0xFD61, 0x0000, 0x05C0, 0x05C0, 0x0000,
 0x0000, 0x0000, 0x0000, 0xFD61, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFD61, 0xFD61, 0x05C0
};


// enemy ship that spawns at the top of the screen
// moves eccentrically to the players height level and shoots
// width=13 x height=12
const unsigned short mutantSprite[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0xAB44, 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0xAB44, 0x0000, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0xAB44, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0xF81F, 0xAB44, 0xF81F, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0xF81F, 0xAB44, 0xF81F, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x05C0, 0x0000, 0x593F, 0x593F, 0xF81F, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x05C0, 0x593F, 0x593F, 0x0000, 0x05C0, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x593F, 0x593F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// if the player shoots a mutant this shows up for a second or so
// width=13 x height=12
const unsigned short deadMutantSprite[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// after one frame of an enemy's unique death sprite, a generic explosion shows before fading to black
// width=13 x height=12
const unsigned short explosionSprite[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// humans are picked up by landers. you need to catch them
//spawned at the bottom at the game start
// width=7 x height=12
const unsigned short humanSprite[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xAB44, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xAB44, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xAB44, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0xF81F, 0xAB44, 0xF81F, 0x0000, 0x0000,
 0x0000, 0x0000, 0xF81F, 0xAB44, 0xF81F, 0x0000, 0x0000,
 0x0000, 0x0000, 0xFD61, 0x05C0, 0xF81F, 0x0000, 0x0000,
 0x0000, 0x0000, 0xFD61, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x05C0, 0x05C0, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// what the player shoots
// width=12 x height=2
const unsigned short playerShot[] = {
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800,0xF800, 0xF800, 0xF800, 0x0000, 0x0000,
 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,0xF800, 0xFFFF, 0xFFFF, 0x0000, 0x0000
};

// what enemies shoot
// width=7 x height=7
const unsigned short enemyShot[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// black box of the ship's dimensions to allow faster travel
const unsigned short ship_black[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// black box of the ship's dimensions to allow faster travel
const unsigned short ship_moving_black[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 
};

//player ship facing right
// width=15 x height=8
const unsigned short ship_right[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0xF83F, 0xF85F, 0xF85F, 0xB514, 0xFFFE, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x20FD, 0xF81F, 0xF81F, 0xF81F, 0xF81F, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xF81F, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0x20FD, 0xED00, 0x079F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20FD, 0xB4F3,
 0xB4F3, 0xB4F3, 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0xB4F3,
 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};

//player ship moving facing right
// width= 19 height= 8
const unsigned short ship_moving_right[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20FD, 0x0000, 0xF83F, 0xF85F, 0xF85F, 0xB514, 0xFFFE, 0x07E0,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20FD, 0x20FD, 0x079F, 0x20FD, 0xF81F, 0xF81F, 0xF81F,
 0xF81F, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F4, 0x0000, 0x0000, 0x0000, 0x0000, 0x20FD, 0x23FF, 0x23FF, 0x079F, 0x079F,
 0xF81F, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0x20FD, 0xED00, 0x079F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20FD,
 0x20FD, 0x079F, 0x20FD, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x20FD, 0x0000, 0xB4F3, 0xB4F3, 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};

//player ship facing left
// widtth=15 x height=8
const unsigned short ship_left[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0xFFFE, 0xB514, 0xF85F, 0xF85F, 0xF83F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xB4F4, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xF81F, 0xF81F, 0xF81F, 0xF81F, 0x20FD, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x079F, 0xED00, 0x20FD, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xF81F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0x20FD, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0xB4F3, 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};

//player ship moving facing left
// width= 19 height= 8
const unsigned short ship_moving_left[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0xFFFE, 0xB514, 0xF85F, 0xF85F, 0xF83F, 0x0000,
 0x20FD, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F4, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xF81F, 0xF81F,
 0xF81F, 0xF81F, 0x20FD, 0x079F, 0x20FD, 0x20FD, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x079F, 0xED00, 0x20FD, 0xB4F3,
 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0xF81F, 0x079F, 0x079F, 0x23FF, 0x23FF, 0x20FD, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0xB4F3, 0xB4F3, 0xB4F3, 0x20FD, 0x079F, 0x20FD, 0x20FD, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0xB4F3, 0xB4F3, 0x0000, 0x20FD, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB4F3, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};

const unsigned short deadPlayer[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};


#endif /* __images_h */
