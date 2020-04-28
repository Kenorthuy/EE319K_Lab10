//SysTick.c

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ADC.h"
#include "creatures.h"


// ****** Global Variables and #defines ******************
uint32_t lastADCData = 10;
uint32_t ADCMail;
uint8_t playerPotFlag;
uint8_t newYPos;
uint8_t newXPos;
#define potOffset 12

// ************** SysTick_Init **************************************
// sets SysTick to run periodic interrupts at a rate of 30Hz
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x0028B0A9;	//SysTick periodic interrupts @ 30Hz
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x07;
}

// *************** Convert *******************************************
// converts the ADC data to a value in between 0 and 128
uint32_t Convert(uint32_t ADCData){
	return (ADCData *128) /4096;
}

// ************** SysTick_Handler **********************************
// will check the slide pot and the three buttons at a rate of 30 Hz
// if a change in ADC position or a button is pressed, a global semaphore is set
void SysTick_Handler(void){//uint8_t convertedValue;
	ADCMail = Convert(ADC_In()) ;
	if(ADCMail != lastADCData){
		player[0].newypos = ADCMail + potOffset;
		//player[0].ypos = convertedValue;
		playerPotFlag = 1;
		player[0].movingFlag =1;
		lastADCData = ADCMail;
	}
	
	if((GPIO_PORTE_DATA_R & 0x02) == 2){
		player[0].newxpos = player[0].xpos + player[0].xvel;
		player[0].facingLeft =0;
		player[0].movingFlag =1;
		player[0].thrust =1;
	}
	
	if((GPIO_PORTE_DATA_R & 0x01) == 1){
		player[0].newxpos = player[0].xpos - player[0].xvel;
		player[0].facingLeft =1;
		player[0].movingFlag =1;
		player[0].thrust =1;
	}	
	

}
