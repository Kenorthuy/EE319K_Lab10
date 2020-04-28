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
#include "Creatures.h"
#include "Images.h"
#include "SysTick.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void drawCreatures(void);
void Delay100ms(uint32_t count); // time delay in 0.1 seconds
void Input_Init(void);
void LED_Init(void);
void Button_Init(void);
void Intro_Screen(void);
void Level_One(void);


// ************** Intro_Screen *****************************************
void Intro_Screen(void){
	ST7735_DrawBitmap(3, 80, title, 122, 26);
	ST7735_SetCursor(1,10);
	ST7735_SetTextColor(0xFFFF);
	ST7735_OutString("  Press any button\n     to continue.");
	while(GPIO_PORTE_DATA_R == 0);
}

// ***************** Level_One *****************************************
// where we can set all of the enemy settings and timers related to the first level
void Level_One(void){
	ST7735_FillScreen(0x0000);

	ST7735_SetCursor(1,7);
	ST7735_OutString("     Level One");
	ST7735_SetTextColor(0xFFFF);
	Delay100ms(30);
}
// *************** Button_Init **********************************************
void Button_Init(void){
  GPIO_PORTE_DIR_R &= ~(0x07);        
  GPIO_PORTE_DEN_R |= 0x07;         
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

// *************** Input_Init *****************************************
void Input_Init(void){volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x3B;
	delay = SYSCTL_RCGCGPIO_R;
	ADC_Init();
	LED_Init();
	Button_Init();
	
}

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
	SysTick_Init();
	Input_Init();
  Output_Init();					// for ST7735
	Timer1_Init(1454480);
	Intro_Screen();

	Level_One();
  ST7735_FillScreen(0x0000);            // set screen to black

	//ST7735_DrawBitmap(1, 110, landerSprite, 13,12);
	//ST7735_DrawBitmap(21, 110, mutantSprite, 13,12);
  ST7735_DrawBitmap(41, 110, humanSprite, 7,12);
	ST7735_DrawFastHLine(1, 100, 128, 0xAB44);

  Delay100ms(50);              // delay 5 sec at 80 MHz
	EnableInterrupts();
	
  while(1){
		ST7735_DrawFastHLine(1, 100, 128, 0xAB44);			//re-renders the background
		if(enemyflag) {
			enemyflag = 0;
			enemyMove();																	//move enemies
			drawCreatures();															//use updated coordinates to draw creatures
		}
  }

}

void drawCreatures() {
	for(int i = 0; i < 1; i++) {
		if(humans[i].dead == 0) {
			ST7735_DrawBitmap(humans[i].xpos, humans[i].ypos, humanSprite, humans[i].width, humans[i].height);
		}
	}
	for(int i = 0; i < 2; i++) {											//only supports array maximums of two and landers
		if(enemies[i].type == 1 && enemies[i].dead == 0) {
			ST7735_DrawBitmap(enemies[i].xpos, enemies[i].ypos, landerSprite, enemies[i].width, enemies[i].height);
		}
	}
	for(int i = 0; i < 5; i++) {											//only supports array maximums of two and landers
		if(shots[i].override == 0) {
			ST7735_DrawBitmap(shots[i].xpos, shots[i].ypos, enemyShot, 7, 7);
		}
	}
	for(int i = 0; i < 1; i++){
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

// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays
void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}
