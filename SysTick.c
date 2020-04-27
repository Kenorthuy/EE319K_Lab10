//SysTick.c

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ADC.h"
#include "creatures.h"


// ****** Global Variables and #defines ******************
uint32_t lastADCData = 10;
uint32_t ADCMail;
uint8_t playerPotFlag;
uint8_t convertedValue;
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
	ADCMail = ADC_In();
	if(ADCMail != lastADCData){
		convertedValue = Convert(ADCMail) + potOffset;
		//player[0].ypos = convertedValue;
		playerPotFlag = 1;
		player[0].movingFlag =1;
		lastADCData = ADCMail;
	}else{
		playerPotFlag = 0;
		player[0].movingFlag =0;
	}
}
