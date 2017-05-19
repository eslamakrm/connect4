#define SIZE_ROWS 6
#define SIZE_COLS 7
#define INF 999999

#include "renderer.c"

char board[SIZE_ROWS][SIZE_COLS]; //the array that holds the current state of the game
char players[2] = {'X', 'O'}; 		//the 2 available players
int tops[SIZE_COLS]; 							//counters for the current position to fill in each col of the board
int selected = 0; 
int player = 0; 									//the current player of the game 
int ai_player = 1; 								//the Opponnent or ai player 


//Make the initial state of the game
void board_init()
{
    int i, j;
		Nokia5110_ClearBuffer();
		Nokia5110_DisplayBuffer(); 
    for (i = 0; i < SIZE_ROWS; i++)
    {
        tops[i] = 0;
        for (j = 0; j < SIZE_COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
		render_board();
		draw_select(0, players[player]);
}


//Score function which determine the score of a given board 
int win(char board[][SIZE_COLS], int rows, int cols, char player)
{
    int i, j, score = 0, total = 0;
    int scores[4] = {0, 1, 5, 10};


    for (i = 0; i < rows; i++)
    {
        int count = 0;
        for (j = 0; j < cols; j++)
        {
            if (board[i][j] == player)
            {
                score++;

                if (++count == 4)
                    return INF;
            }
            else
            {
                count = 0;
                if (board[i][j] != ' ')
                {
                    score = 0;
                }
            }
        }
        total += scores[score];
        score = 0;
    }

    for (i = 0; i <= rows; i++)
    {
        int count = 0;
        for (j = 0; j <= cols; j++)
        {
            if (board[j][i] == player)
            {
                score++;
                
                if (++count == 4)
                    return INF;
            }
            else
            {
                count = 0;
                if (board[i][j] != ' ')
                {
                    score = 0;
                }
            }
        }
        total += scores[score];
        score = 0;
    }

    for (i = 0; i < 3; i++)
    {
        int count = 0;
        for (j = 0; j < rows; j++)
        {

            if (j + i < rows && board[j + i][j] == player)
            {
                score++;
                
                if (++count == 4)
                    return INF;
            }
            else
            {
                count = 0;
                if (board[i][j] != ' ')
                {
                    score = 0;
                }
            }
        }
        total += scores[score];
        score = 0;
    }

    for (i = 1; i < 4; i++)
    {
        int count = 0;
        for (j = 0; j < rows; j++)
        {
            if (j + i < cols && board[j][j + i] == player)
            {
                score++;
                
                if (++count == 4)
                    return INF;
            }
            else
            {
                count = 0;
                if (board[i][j] != ' ')
                {
                    score = 0;
                }
            }
        }
        total += scores[score];
        score = 0;
    }

    for (i = 0; i < 4; i++)
    {
        int count = 0;
        for (j = 0; j < rows; j++)
        {
            if (rows - j - i >= 0 && board[j][rows - j - i] == player)
            {
                score++;
                
                if (++count == 4)
                    return INF;
            }
            else
            {
                count = 0;
                if (board[i][j] != ' ')
                {
                    score = 0;
                }
            }
        }
        total += scores[score];
        score = 0;
    }

    for (i = 1; i < 3; i++)
    {
        int count = 0;
        for (j = 0; j < rows; j++)
        {
            if (j + i < rows && board[j + i][rows - j] == player)
            {
                score++;
                
                if (++count == 4)
                    return INF;
            }
            else
            {
                count = 0;
                if (board[i][j] != ' ')
                {
                    score = 0;
                }
            }
        }
        total += scores[score];
        score = 0;
    }

    return total;
}

//Check for ties
int board_tie(){
	int i;
	for(i = 0; i < SIZE_COLS; i++){
		if(tops[i] != SIZE_ROWS)
			return 0;
	}
	
	return 1;
}

//Game that handles a new move and check for illigal moves
int play(int position)
{
    if (position >= SIZE_COLS || tops[position] >= SIZE_ROWS)
        return -1;
    board[tops[position]++][position] = players[player];
    render(position, SIZE_ROWS - tops[position], players[player]);

    if (win(board, SIZE_ROWS, SIZE_COLS, players[player]) == INF)
    {
        return players[player];
    }

    player = (player + 1) % 2;
	
    return 0;
}


void select(int pos){
	draw_select(pos, players[player]);
}

//Handle the game over situation
void gameover(char winner){
	if(winner == players[ai_player])
	{
		render_gameover(1);
		GPIO_PORTF_DATA_R = 2;
	}
	else if(winner == 'T')
	{
		render_gameover(3);
		GPIO_PORTF_DATA_R = 10;
	}
	else 
	{
		render_gameover(2);
		GPIO_PORTF_DATA_R = 8;
	}
}
