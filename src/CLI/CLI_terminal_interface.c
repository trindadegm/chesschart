#include <stdio.h>
#include <string.h>

#include <CCH/CCH_mechanics.h>
#include <CLI/CLI_terminal_interface.h>

char g_pieceStrArray[13][3] = 
  {CODED_CHESS_P, CODED_CHESS_N, CODED_CHESS_B, CODED_CHESS_R, CODED_CHESS_Q, CODED_CHESS_K,
   "  ", CODED_CHESS_P, CODED_CHESS_N, CODED_CHESS_B, CODED_CHESS_R, CODED_CHESS_Q, CODED_CHESS_K};

// Print the state of the board
// There are colors, for UNIX, DON'T WINDOWS-MIZE-IX THIS!
int CLI_print_state_board(const CCH_State* state)
{
  bool whiteSquare = false;

  for (int y = 7; y > -1; --y)
  {
    printf("\t\x1b[0m\x1b[91m%d ", y+1);
    for (int x = 0; x < 8; ++x)
    {
      if (whiteSquare)
      {
        printf("\x1b[0;44m");
      }
      else
      {
        printf("\x1b[0;104m");
      }
      whiteSquare = !whiteSquare;

      CCH_Piece p = state->board[x][y];
      if (CCH_is_white(p))
        printf("\x1b[97m%s", g_pieceStrArray[p]);
      else
        printf("\x1b[30m%s", g_pieceStrArray[p]);
    }
    printf("\n");
    whiteSquare = !whiteSquare;
  }

  printf("\t\x1b[0m\x1b[91m  ");
  for (char c = 'a'; c < 'i'; ++c)
  {
    printf("%c ", c);
  }
  printf("\x1b[0m\n\n");
  return 0;
}

int CLI_interface_play(const CCH_State* startingState, CCH_Player player)
{
  CCH_State state = *startingState; // Copy the state
  CCH_Player toPlay = CCH_WHITES; // Whites first
  int code = 0;

  while (code != EOF)
  {
    CCH_Move mv;
    char command[32];

    CLI_print_state_board(&state);

    if (toPlay == player)
    {
      printf("(cch:play)> ");
      code = scanf("%31s", command);
      if (strcmp(command, "exit") == 0)
      {
        code = EOF;
      }
      else if (strcmp(command, "p") == 0)
      {
        code = scanf("%hd,%hd %hd,%hd", &mv.from.x, &mv.from.y, &mv.to.x, &mv.to.y);
        CCH_move_piece(&state, mv);
      }

      player = CCH_BLACKS;
    }
    else
    {
      int x, y;
      printf("Select\n");
      scanf("%d,%d", &x, &y);
      CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS];
      CCH_list_piece_moves(&state, x, y, moves);
      for (int i = 0; i < CCH_MAX_PIECE_MOVEMENTS; ++i)
      {
        if (moves[i].to.x == -1)
        {
          printf("END\n");
          break;
        }
        printf("%d,%d %d,%d\n", moves[i].from.x, moves[i].from.y, moves[i].to.x, moves[i].to.y);
      }
      // Computer
      player = CCH_WHITES;
    }
  }
  printf("\n");

  return 0;
}
