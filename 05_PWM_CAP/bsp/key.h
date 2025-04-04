#ifndef _KEY_H
#define _KEY_H

#include"main.h"
#include "stdbool.h"

extern uint16_t duty;
extern uint32_t fre;

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
	uint8_t justify_state;
	bool level_state;
	bool final_state;
}Button;

void KEY_Detect(void);
void KEY_Proc(void);

	


#endif
 
