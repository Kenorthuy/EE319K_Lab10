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
 
// ******* Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// Left button connected to PE0
// Right button connected to PE1
// Fire Button connected to PE2
// 32*R resistor DAC bit 0 on PB0 (least significant bit)
// 16*R resistor DAC bit 1 on PB1
// 8*R resistor DAC bit 2 on PB2
// 4*R resistor DAC bit 3 on PB3
// 2*R resistor DAC bit 4 on PB4
// 1*R resistor DAC bit 5 on PB5 (most significant bit)

// LED on PB4
// LED on PB5

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
#include "Images.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void drawCreatures(void);
void Delay100ms(uint32_t count); // time delay in 0.1 seconds

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
	
	initCreatures();

  Output_Init();
  ST7735_FillScreen(0x0000);            // set screen to black

	//ST7735_DrawBitmap(1, 110, landerSprite, 13,12);
	//ST7735_DrawBitmap(21, 110, mutantSprite, 13,12);
  //ST7735_DrawBitmap(41, 110, humanSprite, 7,12);
	ST7735_DrawBitmap(91, 110, humanSprite, 7,12);
	ST7735_DrawFastHLine(1, 100, 128, 0xAB44);

  Delay100ms(50);              // delay 5 sec at 80 MHz
	
  while(1){
		Delay100ms(2);
		ST7735_DrawFastHLine(1, 100, 128, 0xAB44);			//re-renders the background
		enemyMove();																		//move enemies
		drawCreatures();																//use updated coordinates to draw people
  }

}

void drawCreatures() {
	for(int i = 0; i < 2; i++) {											//only supports array maximums of two and landers
		if(enemies[i].type == 1) {
			ST7735_DrawBitmap(enemies[i].xpos, enemies[i].ypos, landerSprite, enemies[i].width, enemies[i].height);
		}
	}
	for(int i = 0; i < 2; i++) {
		ST7735_DrawBitmap(humans[i].xpos, humans[i].ypos, humanSprite, humans[i].width, humans[i].height);
	}
}

void Systick_Handler() {
	//write this later. use a mailbox to check inputs. i think Timer1 should connect to enemies so that everything has a reasonable scope
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
