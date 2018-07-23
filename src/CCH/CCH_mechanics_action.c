#include <CCH/CCH_mechanics.h>

#include <malloc.h>

// Documentation on CCH_mechanics.h
int CCH_move_piece(CCH_State* state, CCH_Move mv)
{
  // Just a switch on the pieces
  CCH_Piece toMove = state->board[mv.from.x][mv.from.y];
  state->board[mv.from.x][mv.from.y] = CCH_NO_PIECE;
  state->board[mv.to.x][mv.to.y] = toMove;

  // Now, record this movement into a list
  if (state->stateMoveData == NULL) // It is the first movement, so it must ve allocated on the state
  {
    state->stateMoveData = malloc(sizeof(CCH_StateMoveData));
    state->stateMoveData->prev = NULL;
  }
  else // Not the first movement, so it must be allocated on a pointer, and replaced on the state
  {
    CCH_StateMoveData* newPrevStateData = malloc(sizeof(CCH_StateMoveData));
    CCH_StateMoveData* temp = state->stateMoveData;
    state->stateMoveData = newPrevStateData;
    state->stateMoveData->prev = temp;
  }
  state->stateMoveData->move = mv;
  state->stateMoveData->aval = 0.0f;

  return 0;
}

float CCH_aval_simple_pos(const CCH_State* state)
{
  return 0.0f;
}
