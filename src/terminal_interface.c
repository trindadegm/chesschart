#include <terminal_interface.h>

#include <CCH/CCH_mechanics.h>
#include <stdio.h>

char g_pieceStrArray[13][3] = 
  {CODED_CHESS_W_P, CODED_CHESS_W_N, CODED_CHESS_W_B, CODED_CHESS_W_R, CODED_CHESS_W_Q, CODED_CHESS_W_K,
   "  ", CODED_CHESS_B_P, CODED_CHESS_B_N, CODED_CHESS_B_B, CODED_CHESS_B_R, CODED_CHESS_B_Q, CODED_CHESS_B_K};

// Print the state of the board
// There are colors, for UNIX, DON'T WINDOWS-MIZE-IX THIS!
int print_state_board(const CCH_State* state)
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
  printf("\n\n");
  
  return 0;
}
