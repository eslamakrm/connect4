#include "ports.h"

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     		// 1) F clock
  delay = SYSCTL_RCGC2_R;           		// delay    
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   		// 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;          		// allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        		// 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   		// 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = ~(0x11);          	 	// 5) PF0-PF4 input   
  GPIO_PORTF_AFSEL_R = 0x00;        		// 6) no alternate function
  GPIO_PORTF_PUR_R  = 0x11;          		// enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R  = 0x1F;         		// 7) enable digital pins PF4-PF0  
	GPIO_PORTF_IS_R = 0x00;								// Set the interrupt sense to edge-sensitive
	GPIO_PORTF_IBE_R = 0x00;							// Interrupt controlled by both IEV	
	GPIO_PORTF_IEV_R = 0x00;
	GPIO_PORTF_IM_R = 0x00;								// Listen to on PF0, PF1, PF4
	NVIC_EN0_R = 0x40000000; 
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;
	GPIO_PORTF_ICR_R = 0x1F;
}


