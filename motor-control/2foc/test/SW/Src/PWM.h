//   
//  PWM related rouines:
//  
//  Initialization, control and fault management 
//  
// 
#ifndef __PWM_H
#define __PWM_H

#include <pwm12.h>

void SetupPWM(void);
void PWMDisable(void);
void PWMEnable(void);
int PWMTestPDN(void);
void PWMCycle(int e, int l);
void PWMGetState(int *e, int *l);
int PWMTestCurrent(int wired, int *resI1, int *resI2, int th, int tl);
void PWMTestProtection();

typedef enum { 
	 PWMMOS_XL,
	 PWMMOS_XH,
 	 PWMMOS_YL,
	 PWMMOS_YH,
 	 PWMMOS_ZL,
	 PWMMOS_ZH
} tPWMMOS;
 	
#endif
