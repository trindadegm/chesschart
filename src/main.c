#include <stdio.h>
#include <string.h>

#include <CCH/CCH_definitions.h>
#include <CCH/CCH_mechanics.h>

#include <CLI/CLI_terminal_interface.h>

int main(void)
{
  CCH_State state;
  bool exit = false;

  // Creates a initial state (standart)
  state = (CCH_State) {{
    // Initial piece positions
    {CCH_WHITE_ROOK,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_ROOK},
    {CCH_WHITE_KNIGHT,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_KNIGHT},
    {CCH_WHITE_BISHOP,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_BISHOP},
    {CCH_WHITE_QUEEN,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_QUEEN},
    {CCH_WHITE_KING,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_KING},
    {CCH_WHITE_BISHOP,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_BISHOP},
    {CCH_WHITE_KNIGHT,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_KNIGHT},
    {CCH_WHITE_ROOK,CCH_WHITE_PAWN,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_NO_PIECE,CCH_BLACK_PAWN,CCH_BLACK_ROOK}},

    // Initial player
    CCH_WHITES,

    // Initial round
    0,
  
    // White king made no rock
    false,
    // White king did not move
    false,
    // No white rooks moved
    false,
    false,
    // Black king made no rock
    false,
    // Black king did not move
    false,
    // No black rooks moved
    false,
    false,
  
    // There is no movements until this point
    NULL};

  CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS];
  CCH_list_piece_moves(&state, 4, 4, moves);

  printf("\tChessChart v0.1.0\n\n");
  while (!exit)
  {
    char command[32];
    int code;

    printf("(cch)> ");
    code = scanf("%31s", command);

    if (strcmp(command, "exit") == 0 || code == EOF)
    {
      exit = true;
    }
    if (strcmp(command, "play") == 0)
    {
      code = scanf("%31s", command);
      if (strcmp(command, "whites") == 0)
      {
        CLI_interface_play(&state, CCH_WHITES);
      }
      else if (strcmp(command, "blacks") == 0)
      {
        CLI_interface_play(&state, CCH_BLACKS);
      }
      else
      {
        printf("Invalid option \"%s\".\n", command);
      }
    }
  }

  return 0;
}
