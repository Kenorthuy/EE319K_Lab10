// Defender.c
// Runs on LM4F120/TM4C123
// Evan Varghese and Ken Nguyen

// Last Modified: 1/17/2020

// SOURCE CODE OF ORIGINAL GAME
// http://tech.quarterarcade.com/tech/MAME/src/williams.c.html.aspx?g=737

// GAMEPLAY OVERVIEW
// https://www.youtube.com/watch?time_continue=50&v=PAM7_-_Ycxw&feature=emb_title
// http://www.digitpress.com/dpsoundz/mp3/conquer_the_video_craze/conquer_the_video_craze_03_-_Defender.mp3
// https://www.arcade-museum.com/game_detail.php?game_id=7547

// sounds at https://seanriddle.com/willy2.html
// 				and http://www.digitpress.com/dpsoundz/soundfx.htm
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2019

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2019

 Copyright 2019 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Left button connected to PE0
// Right button connected to PE1
// Fire Button connected to PE2
// 32*R resistor DAC bit 0 on PB0 (least significant bit)
// 16*R resistor DAC bit 1 on PB1
// 8*R resistor DAC bit 2 on PB2
// 4*R resistor DAC bit 3 on PB3
// 2*R resistor DAC bit 4 on PB4
// 1*R resistor DAC bit 5 on PB5 (most significant bit)

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Print.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Timer2.h"
#include "Creatures.h"
#include "Images.h"
#include "SysTick.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void drawCreatures(void);
void Delay100ms(uint32_t count); // time delay in 0.1 seconds
void Input_Init(void);
void LED_Init(void);
void drawBackground(void);
void Button_Init(void);
void Intro_Screen(void);
void Level_One(void);
void Display_Score(void);
void Game_Over(void);

uint8_t Language; // 0 is for english, 1 is for spanish



// ************** Intro_Screen *****************************************
void Intro_Screen(void){
	Output_Clear();
	ST7735_DrawBitmap(3, 80, title, 122, 26);
	ST7735_SetCursor(2,10);
	ST7735_SetTextColor(0xFFFF);
	if(Language ==1){
		ST7735_OutString("Presione cualquier\n      bot\xA2n para\n      continuar");	
	}else{
		ST7735_OutString(" Press any button\n     to continue.");
	}
	while(GPIO_PORTE_DATA_R == 0);
	while(GPIO_PORTE_DATA_R ==1);
}

// ************** Language Select *****************************************
void Language_Select(void){uint32_t langADC;
	Output_Clear();
	ST7735_DrawBitmap(42, 60, globe, 44, 44);
	ST7735_SetCursor(5,7);
	Output_Color(0xFFFFFFFF);
	ST7735_OutString("Select your\n      language.");
	ST7735_SetCursor(5,10);
	ST7735_OutString("  English");
	ST7735_SetCursor(5,11);
	ST7735_OutString("  Espa\xA4ol");

	while((GPIO_PORTE_DATA_R) == 0){
		langADC = ADC_In();	
		langADC /= 2028;
			if(langADC == 0){
				ST7735_SetCursor(5,11);
				ST7735_OutString("  ");
				ST7735_SetCursor(5,10);
				ST7735_OutString(">>");
				Language = 0;
			}else{
				ST7735_SetCursor(5,10);
				ST7735_OutString("  ");
				ST7735_SetCursor(5,11);
				ST7735_OutString(">>");
				Language = 1;
			}
	}
	while(GPIO_PORTE_DATA_R != 0);
}

// ***************** Level_One *****************************************
// where we can set all of the enemy settings and timers related to the first level
void Level_One(void){
	Output_Clear();
	ST7735_SetCursor(6,7);
	if(Language == 1){
		ST7735_OutString("Nivel Uno");
		ST7735_SetCursor(6,9);
		ST7735_OutString("Vidas: 3");
	}else{
		ST7735_OutString("Level One");
		ST7735_SetCursor(6,9);
		ST7735_OutString("Lives: 3");
	}
	ST7735_SetCursor(13,8);
	ST7735_SetTextColor(0xFFFF);
	Level =1;
	player[0].facingLeft = 0;
	Delay100ms(30);
}

// ***************** Game_Over *************************************
// shows that the game is over and then displays the player's score
void Game_Over(void){
	
}

// *************** Button_Init **********************************************
void Button_Init(void){
  GPIO_PORTE_DIR_R &= ~(0x7);        
  GPIO_PORTE_DEN_R |= 0x7;         
}

// *************** LED_Init **********************************************
void LED_Init(void){
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R |= 0x07;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R |= 0x07;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_DEN_R |= 0x07;          // 7) enable digital I/O on PF4-0
}

// *************** Input_Init ********************************************
void Input_Init(void){volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x3B;
	delay = SYSCTL_RCGCGPIO_R;
	ADC_Init();
	LED_Init();
	Button_Init();
}

// *************** drawCreatures ****************************************
// This method renders humans, enemies, the player, and projectiles
// Input: None
// Output: None
void drawCreatures() {
	for(int i = 0; i < 1; i++) {											//draws the humans that arent dead
		if(humans[i].dead == 0) {
			ST7735_DrawBitmap(humans[i].xpos, humans[i].ypos, humanSprite, humans[i].width, humans[i].height);
		}
		if(humans[i].dead == 1) {
			ST7735_DrawBitmap(humans[i].xpos, humans[i].ypos, deadMutantSprite, humans[i].width, humans[i].height);
		}
	}
	for(int i = 0; i < 2; i++) {											//only supports array maximums of two and landers
		if(enemies[i].type == 1 && enemies[i].dead == 0) {		//draws landers that arent dead
			ST7735_DrawBitmap(enemies[i].xpos, enemies[i].ypos, landerSprite, enemies[i].width, enemies[i].height);
		}
		if(enemies[i].type == 1 && enemies[i].dead == 1) {		//draws landers that are dead
			ST7735_DrawBitmap(enemies[i].xpos, enemies[i].ypos, deadLanderSprite, enemies[i].width, enemies[i].height);
		}
		if(enemies[i].type == 1 && enemies[i].dead == 2) {		//draws landers that are dead
			ST7735_DrawBitmap(enemies[i].xpos, enemies[i].ypos, explosionSprite, enemies[i].width, enemies[i].height);
		}
	}
	for(int i = 0; i < 5; i++) {
		if(shots[i].override == 0) {										//if a shot exists, show it
			ST7735_DrawBitmap(shots[i].xpos, shots[i].ypos, enemyShot, 7, 7);
		}
		if(shots[i].override == 1) {										//if a shot does not exist, print a black rectangle over it
			ST7735_FillRect(shots[i].xpos, shots[i].ypos, 7, 7, 0x0000);
		}
	}
	for(int i = 0; i < 10; i++) {
		if(lasers[i].override == 0) {										//if a shot exists, show it
			ST7735_DrawBitmap(lasers[i].xpos, lasers[i].ypos, playerShot, 12, 2);
		}
		if(lasers[i].override == 1) {										//if a shot does not exist, print a black rectangle over it
			ST7735_FillRect(lasers[i].xpos, lasers[i].ypos, 12, 2, 0x0000);
		}
	}
	for(int i = 0; i < 1; i++){												//print the player using movement information
		if(player[0].movingFlag == 1 && player[0].facingLeft == 0){
			/*if(player[0].thrust ==1){
				ST7735_DrawBitmap(player[i].xpos, player[i].ypos, ship_moving_black, player[i].width + 4, player[i].height);
				ST7735_DrawBitmap(player[i].newxpos, player[i].newypos, ship_moving_right, player[i].width + 4, player[i].height);		//moving to the right				
			}else{*/
				ST7735_DrawBitmap(player[i].xpos, player[i].ypos, ship_black, player[i].width, player[i].height);
				ST7735_DrawBitmap(player[i].newxpos, player[i].newypos, ship_right, player[i].width, player[i].height);		//moving to the right
			//}
			player[i].movingFlag = 0;
			//player[i].thrust =0;
			player[i].ypos = player[i].newypos; 
			player[i].xpos = player[i].newxpos;
		}

		if(player[0].movingFlag == 1 && player[0].facingLeft == 1){
			/*if(player[0].thrust ==1){
				ST7735_DrawBitmap(player[i].xpos, player[i].ypos, ship_moving_black, player[i].width + 4, player[i].height);
				ST7735_DrawBitmap(player[i].newxpos, player[i].newypos, ship_moving_left, player[i].width + 4, player[i].height);		//moving to the right				
			}else{*/
				ST7735_DrawBitmap(player[i].xpos, player[i].ypos, ship_black, player[i].width, player[i].height);
				ST7735_DrawBitmap(player[i].newxpos, player[i].newypos, ship_left, player[i].width, player[i].height);   //moving to the left
			//}
			player[i].movingFlag = 0;
			//player[i].thrust =0;
			player[i].ypos = player[i].newypos; 
			player[i].xpos = player[i].newxpos;
		}
	}
}

// *************** drawBackground ****************************************
// This method quickly renders the basic background and the number of player lives.
// Input: None
// Output: None
void drawBackground() {
	char lives[5] = {'L','I','V','E','S'};								//load up an array of characters to print
	int spot = 0;
	ST7735_DrawFastHLine(1, 105, 128, 0xAB44);						//draw a brown line to represent the horizon
	ST7735_DrawString(1, 12, lives, 0xFFFF);							//print "LIVES"
	for(int i = 0; i < player[0].lives; i++) {						//iterate through existing lives
		ST7735_FillRect(40+10*spot, 121, 5, 5, 0xF800);			//a red rectangle means theres a life
		spot++;																							//this value modifies the x position
	}
	for(int i = player[0].lives; i < 3; i++) {						//overwrites lost lives with a black rectangle
		ST7735_FillRect(40+10*spot, 121, 6, 6, 0x0000);
		spot++;
	}
}

//hard coded delay function
void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

// ****************** Display_Score **************************************
// displays in-game score below lives
void Display_Score(void){
	char score[5] = {'S','C','O','R','E'};		
	ST7735_DrawString(1, 13, score, 0xFFFF);
	ST7735_SetCursor(7,13);
	LCD_OutDec(Score);
	
	
}

// *************** MAIN **************************************************
int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
	SysTick_Init();
	Input_Init();
	Output_Init();
	
	Timer1_Init(1454480);
	Timer2_Init(2);
	//ADC_Init();
	Language_Select();
	Intro_Screen();
	

  Level_One();
  ST7735_FillScreen(0x0000);            // set screen to black

	//ST7735_DrawBitmap(1, 110, landerSprite, 13,12);
	//ST7735_DrawBitmap(21, 110, mutantSprite, 13,12);

  Delay100ms(10);              					// delay 1 sec at 80 MHz
	EnableInterrupts();
	
  while(1){
		if(gameDone) {
			Game_Over();
			ST7735_FillScreen(0x0000);            // set screen to black
		}
		else if(enemyflag) {
			enemyflag = 0;
			enemyMove();													//move enemies
			drawBackground();											//re-render background
			drawCreatures();											//use updated coordinates to draw creatures
			Display_Score();
		}
  }
}


