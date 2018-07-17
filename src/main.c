#include <stdio.h>

#include <CCH/CCH_definitions.h>
#include <CCH/CCH_mechanics.h>

int main(void)
{
  printf("ChessChart v0.0.2\n");  

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

  for (int i = 0; i < CCH_MAX_PIECE_MOVEMENTS; ++i)
  {
    if (moves[i].to.x == -1 && moves[i].to.y == -1) break;
    printf("%d %d :: %d %d\n", moves[i].from.x, moves[i].from.y, moves[i].to.x, moves[i].to.y);
  }

  return 0;
}
