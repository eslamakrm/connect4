#include "Nokia5110.h"
#include "Random.h"

const unsigned char white[] ={
 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xF0, 0x0F,
 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF,

};

const unsigned char black[] ={
 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF,

};

const unsigned char space[] ={
 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};

const unsigned char square_black[] ={
 0x42, 0x4D, 0xA6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0x0F,
 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF,
 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,

};


const unsigned char square_blank[] ={
 0x42, 0x4D, 0xA6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0x00,
 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF,
 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,

};


const unsigned char square_white[] ={
 0x42, 0x4D, 0xA6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0x0F,
 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF,
 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,

};

#define width ((unsigned int) square_blank[18])
#define height ((unsigned int) square_blank[22])

//Initialize the nokia driver
void renderer_init(){
	Random_Init(1);
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();      // draw buffer
}

//Render a position when a new move occures
void render(int pos_x, int pos_y, char player){
	if(player == 'X'){
		Nokia5110_PrintBMP(width*pos_x, (2+pos_y)*height, square_black, 0);
	}else if(player == 'O'){
		Nokia5110_PrintBMP(width*pos_x, (2+pos_y)*height, square_white, 0);
	}
	Nokia5110_DisplayBuffer();
}

//Draw the selected position for the current player
void draw_select(int pos, char player){
	int i;
	for(i = 0; i < 7; i++){
		if(pos == i){
			if(player == 'X'){
				Nokia5110_PrintBMP(pos*width+((width/2)-black[22]/2), black[22], black, 0);
			}else if(player == 'O'){
				Nokia5110_PrintBMP(pos*width+((width/2)-white[22]/2), white[22], white, 0);
			}
		}else{
			Nokia5110_PrintBMP(i*width+((width/2)-white[22]/2), white[22], space, 0);
		}
	}
	Nokia5110_DisplayBuffer();
}


//Render the game over screen
void render_gameover(int winner){
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();  
	Nokia5110_SetCursor(1, 2);
	Nokia5110_OutString("Game Over");
	Nokia5110_SetCursor(2, 4);
	if(winner == 1){
		Nokia5110_OutString("You lose");
	}else if(winner == 3){
		Nokia5110_OutString("  Tie");
	}else{
		Nokia5110_OutString("You win");
	}
}


//Draw the selction arrow for the game mode selection screen
void select_vertical(int pos){
	int i;
	for(i = 0; i < 3; i++){
		Nokia5110_SetCursor(0, i);
		if(i == pos)	
			Nokia5110_OutChar('>');
		else
			Nokia5110_OutChar(' ');
	}
}

//Draw the selction screen
void render_start(){ 
	Nokia5110_SetCursor(1, 0);
	Nokia5110_OutString("Single(AI)");
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("Single(you)");
	Nokia5110_SetCursor(1, 2);
	Nokia5110_OutString("Multiplayer");
	select_vertical(0);
}

//Render the initial empty board on the screen
void render_board(){
	int i, j;
	for(i = 0; i < 6; i++){
			for(j = 0; j < 7; j++)
				Nokia5110_PrintBMP(width*j, (2+i)*height, square_blank, 0);
	}
	Nokia5110_DisplayBuffer();
}