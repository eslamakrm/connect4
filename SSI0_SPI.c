#include "SSI0_SPI.h"
#include "tm4c123gh6pm.h"

//#define SSI0_Data_R               (*((volatile unsigned long *)0x40008008))


void ssi0_spi_init()
{
  volatile unsigned long delay;
	SYSCTL_RCGC1_R |=(1<<4);
  SYSCTL_RCGC2_R |=(1<<0);
	delay=SYSCTL_RCGCSSI_R;
	delay = (1<<SSI0_clk)|(1<<SSI0_fss)|(1<<SSI0_rx)|(1<<SSI0_tx);
	GPIO_PORTA_AFSEL_R |=delay;
	GPIO_PORTA_AFSEL_R &= ~(1<<SSI0_rx);
	GPIO_PORTA_DEN_R |=delay;
	GPIO_PORTA_PCTL_R |=(2<<SSI0_clk*4)|(2<<SSI0_fss*4)|(2<<SSI0_rx*4)|(2<<SSI0_tx*4);
  GPIO_PORTA_AMSEL_R &=~delay;
	//SSI0_CR1_R =0x00;
	SSI0_CR1_R &= ~(1<<SSE);
	//SSI0_CR1_R =0;
	SSI0_CC_R =0x05;
	SSI0_CPSR_R = 0x02;
	SSI0_CR0_R = (0x7<<DSS);
	//SSI0_DR_R =0xff;
	SSI0_CR1_R |= (1<<SSE);
	
}

void ssi0_spi_TR(unsigned char data)
{
  while((SSI0_SR_R & (1<<BSY)));
	SSI0_DR_R = data;
  while((SSI0_SR_R & (1<<BSY)));	
}
