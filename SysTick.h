#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
// Header files contain the prototypes for public functions
// this file explains what the module does

// ************** Global Variables ******************
// preferably semaphores
extern uint8_t playerPotFlag;
extern uint8_t convertedValue;

// **************SysTick_Init*********************

void SysTick_Init(void);


#endif
