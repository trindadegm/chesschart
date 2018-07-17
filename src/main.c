#include <stdio.h>

#include <CCH/CCH_definitions.h>
#include <CCH/CCH_mechanics.h>

#include <terminal_interface.h>

int main(void)
{
  printf("ChessChart v0.1.0\n\n");  

  CCH_State state;

  // Creates a initial state
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
    // Black king made no rock
    false,
    // Black king did not move
    false,
  
    // There is no previous movement (it says next, but the next is the previous (?))
    {.next = NULL}};

  CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS];
  CCH_list_piece_moves(&state, 4, 4, moves);

  print_state_board(&state);

  // Fix the terminal color even if everything else goes wrong
  printf("\x1b[0m");
  return 0;
}
