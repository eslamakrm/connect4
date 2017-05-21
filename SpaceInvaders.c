// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground


#include "TExaS.h"
#include "PORTS.c"
#include "UART.c"
#include "ai.c"
#include <stdlib.h>
#include <time.h>

int winner = 0; //determine if the board is win or not
int mode = 0; //determine the mode of the game
int seed;

//delay for (count * 1ms)
void Delay1ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 7272;  // 1 msec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

//read the buttons for game controll
void read_buttons(int x){
	int sw1, sw2;
	do{
		sw1 = GPIO_PORTF_DATA_R&(1<<4);
		sw2 = GPIO_PORTF_DATA_R&(1<<0);
		Delay1ms(20); //debounce 
		if(!(sw1)){
			if(mode){
				selected = (selected + 1) % SIZE_COLS;
				select(selected);
			}else{
				selected = (selected + 1) % 2;
				select_vertical(selected);
			}
			while(!(GPIO_PORTF_DATA_R&(1<<4)));
			Delay1ms(20);
		}
	}while(sw2);
		
		switch(x){
			//game mode select
			case 0:
					mode = selected + 1;
					selected = 0;
			break;
			
			//single player mode
			case 2:
				winner = play(selected);
				if(winner == -1) return; //prevent illigal moves
				selected = 0;
				select(selected);
			break;
			case 1:
				winner = play(selected);
				if(winner == -1) return; //prevent illigal moves
				UART_OutChar(selected+'1');
				selected = -1;
				select(selected);
			break;
		}
		while(!(GPIO_PORTF_DATA_R&(1<<0))){seed++;};
}

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay1ms(unsigned long count); // time delay in 1 mseconds

 int main(void){
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	PortF_Init();
	UART_Init();
	EnableInterrupts();
	renderer_init();
	render_start();
	
	 
	do{
		read_buttons(0);
	}while(!mode);
	
	if(mode == 2){
		board_init();
		GPIO_PORTF_DATA_R = 4;
		
		
			ai_player = 1;
		
		Delay1ms(100);
		do{
				do{
					read_buttons(mode);
				}while(winner == -1); //prevent illigal moves
				
				ai(board, tops, 5, -999999, 999999, ai_player, ai_player, &selected);
				winner = play(selected);
				selected = 0;
				select(0);
			
			if(board_tie()){
				winner = 'T';
				break;
			}
			
		}while(!winner);
		
	}
	else if(mode == 1){
		int x, y;
		int start;

		lcd_clear();
		srand(seed);
		x = rand()%9;
		
		UART_OutChar(x + '0');
		
		y = (UART_InChar()-'0');
		
		if(x > y){
			ai_player = 1;
			start = 1;
		}else{
			ai_player = 0;
			start = 0;
		}
		
		board_init();
		GPIO_PORTF_DATA_R = 4;
		
		do{
			if(start){
				do{
					read_buttons(mode);
				}while(winner == -1); //prevent illigal moves
			}else{
				select(-1);
			}
				
				//ai(board, tops, 4, -999999, 999999, ai_player, ai_player, &selected);
				
				do{
					do{
						selected = UART_InChar()-'1';
					  }while(selected >7 || selected < 0);
						winner = play(selected);
				}while(winner == -1);
				
				selected = 0;
				select(0);
			
			if(!start && !winner){
				do{
					read_buttons(mode);
				}while(winner == -1); //prevent illigal moves
			}
			
			if(board_tie() && !winner){
				winner = 'T';
				break;
			}
			
		}while(!winner);
	}
	
  Delay1ms(5000);
	gameover(winner);
}

