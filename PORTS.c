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


void UART_Init(void){
// as part of Lab 11, modify this program to use UART1 instead of UART1
//                 switching from PC5,PC4 to PB1,PB0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART1_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= (1<<9) | (1<<8);
	
  GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB1,PB0
  GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB1,PB0
                                        // configure PB1,PB0 as UART1
  GPIO_PORTB_PCTL_R = 0x00000011;
  GPIO_PORTB_AMSEL_R &= ~0x03;          // disable analog functionality on PB1,PB0
	UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
}
