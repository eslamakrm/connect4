#include "board.c"

//Clone the current board for the minmax algorithm
void clone_board(char board[][SIZE_COLS], char clone[][SIZE_COLS])
{
    int i, j;
    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLS; j++)
        {
							clone[i][j] = board[i][j];
        }
    }
}

//Clone the tops array for the minmax algorithm
void clone_tops(int tops[], int clone[])
{
    int i;
    for (i = 0; i < SIZE_COLS; i++)
        clone[i] = tops[i];
}

//Make a move and check for illigal moves in the cloned board
int play_clone(int position, char board[][SIZE_COLS], int tops[], char player)
{
    if (position >= SIZE_COLS || tops[position] >= SIZE_ROWS)
        return 0;
    board[tops[position]++][position] = player;
  //  render(board, SIZE_ROWS, SIZE_COLS, selected);

    return 1;
}


//Ai based on minmax algorithm 
int ai(char board[][SIZE_COLS], int tops[], int depth, int a, int b, int max_player, int c_player, int *ai_move)
{
    int move_score[2], move = 0;
    int win_score = win(board, SIZE_ROWS, SIZE_COLS, players[max_player]);
    int lose_score = win(board, SIZE_ROWS, SIZE_COLS, players[(max_player + 1) % 2]);
    int i = 0, x;
    int tops_clone[SIZE_COLS];
    char board_clone[SIZE_ROWS][SIZE_COLS];
    
    if (max_player == c_player)
    {
        move_score[0] = -1;
        move_score[1] = -INF;
    }
    else
    {
        move_score[0] = -1;
        move_score[1] = INF;
    }

    if (win_score == INF)
		{
			return INF;//*(depth+1);
		}
    if (lose_score == INF)
		{
			return -(INF);//*(depth+1);
		}

    if (depth == 0)
    {
        if (!max_player)
				{
					return lose_score - win_score;
				}
        else
				{
					return win_score - lose_score;
				}
    }

    if (c_player == max_player)
    {
        for (i = 0; i < SIZE_COLS; i++)
        {
            clone_tops(tops, tops_clone);
            clone_board(board, board_clone);
            move = play_clone(i, board_clone, tops_clone, players[c_player]);

            if (move != 0)
            {
                x = ai(board_clone, tops_clone, depth - 1, a, b, max_player, (c_player + 1) % 2, ai_move);
                if (x > move_score[1])
                {
                    move_score[0] = i;
                    move_score[1] = x;
                    a = x;
                }
                if (b <= a)
                    break;
            }
        }
        *ai_move = move_score[0];
        return move_score[1];
    }
    else
    {
        for (i = 0; i < SIZE_COLS; i++)
        {
            clone_tops(tops, tops_clone);
            clone_board(board, board_clone);
            move = play_clone(i, board_clone, tops_clone, players[c_player]);

            if (move != 0)
            {
                x = ai(board_clone, tops_clone, depth - 1, a, b, max_player, (c_player + 1) % 2, ai_move);
                if (x < move_score[1])
                {
                    move_score[0] = i;
                    move_score[1] = x;
                    b = x;
                }

                if (b <= a)
                    break;
            }
        }
        *ai_move = move_score[0];
        return move_score[1];
    }
}
