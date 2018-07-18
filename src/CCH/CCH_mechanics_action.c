#include <CCH/CCH_mechanics.h>

#include <malloc.h>

// Documentation on CCH_mechanics.h
int CCH_move_piece(CCH_State* state, CCH_Move mv)
{
  // Just a switch on the pieces
  CCH_Piece toMove = state->board[mv.from.x][mv.from.y];
  state->board[mv.from.x][mv.from.y] = CCH_NO_PIECE;
  state->board[mv.to.x][mv.to.y] = toMove;

  return 0;
}
