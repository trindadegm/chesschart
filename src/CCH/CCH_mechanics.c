#include <CCH/CCH_mechanics.h>

// These functions are special cases of the function CCH_list_piece_moves, and are used on
// the function CCH_list_piece_moves, that means they have similar jobs, and therefore
// share almost the same documentation.
//
// As each piece has different moves, different procedures were required to move
// each piece.
int CCH_list_pawn_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_list_knight_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_list_bishop_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_list_rook_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_list_queen_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_list_king_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);

int CCH_take_place_if_allowed(const CCH_State*, const CCH_Move*, int movesAt, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);

// Documentation in CCH_mechanics.h
int CCH_list_piece_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  CCH_Piece piece = state->board[x][y];

  // Moving is different for each piece
  switch (piece)
  {
    case CCH_WHITE_PAWN:
    case CCH_BLACK_PAWN:
      return CCH_list_pawn_moves(state, x, y, moves);
      break;
    case CCH_WHITE_KNIGHT:
    case CCH_BLACK_KNIGHT:
      return CCH_list_knight_moves(state, x, y, moves);
      break;
    case CCH_WHITE_BISHOP:
    case CCH_BLACK_BISHOP:
      return CCH_list_bishop_moves(state, x, y, moves);
      break;
    case CCH_WHITE_ROOK:
    case CCH_BLACK_ROOK:
      return CCH_list_rook_moves(state, x, y, moves);
      break;
    case CCH_WHITE_QUEEN:
    case CCH_BLACK_QUEEN:
      return CCH_list_queen_moves(state, x, y, moves);
      break;
    case CCH_WHITE_KING:
    case CCH_BLACK_KING:
      return CCH_list_king_moves(state, x, y, moves);
      break;
    case CCH_NO_PIECE: // Can't move no piece
      return 1; // A warning, very light one, it it trying to move nothing
      break;
    default:    // Invalid piece found, may be dangerous
      return 2; // A warning
  }
}

int CCH_list_pawn_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  int it = 0;

  assert((x > 0 && y > 0)); // ASSERTION

  CCH_Move mv;
  if (CCH_is_white(state->board[x][y]))
  {
    mv = (CCH_Move) {{x, y}, {x, y+1}};
    if (mv.to.y < 8) // If pawn is moving INBOUNDS
    { 
      it += CCH_take_place_if_allowed(state, &mv, it, moves); // Try to move foward

      if (y == 1 // May move twice and
          && it == 1) // could also move foward without problems
      {
        mv.to.y = y+2; // Set the move to 2 tiles foward
        it += CCH_take_place_if_allowed(state, &mv, it, moves);
      }

      mv.to.x = x+1, mv.to.y = y+1;
      if (mv.to.x < 8) // If x inbounds
      {
        if (CCH_is_black(state->board[mv.to.x][mv.to.y]))
        {
          moves[it++] = mv;
        }
      }

      mv.to.x = x-1;
      if (mv.to.x > 0) // If x still inbounds
      {
        if (CCH_is_black(state->board[mv.to.x][mv.to.y]))
        {
          moves[it++] = mv;
        }
      }
    } // End of if pawn is moving INBOUNDS
  } // End of if it is a white pawn
  else // It is a black pawn (if it is a pawn it can't be no piece
  {
    mv = (CCH_Move) {{x, y}, {x, y-1}};
    if (mv.to.y > -1) // If pawn is moving INBOUNDS
    { 
      it += CCH_take_place_if_allowed(state, &mv, it, moves); // Try to move foward

      if (y == 6 // May move twice and
          && it == 1) // could also move foward without problems
      {
        mv.to.y = y+2; // Set the move to 2 tiles foward
        it += CCH_take_place_if_allowed(state, &mv, it, moves);
      }

      mv.to.x = x+1, mv.to.y = y-1;
      if (mv.to.x < 8) // If x inbounds
      {
        if (CCH_is_black(state->board[mv.to.x][mv.to.y]))
        {
          moves[it++] = mv;
        }
      }

      mv.to.x = x-1;
      if (mv.to.x > 0) // If x still inbounds
      {
        if (CCH_is_black(state->board[mv.to.x][mv.to.y]))
        {
          moves[it++] = mv;
        }
      }
    } // End of if pawn is moving INBOUNDS
  } // End of else (it is a black pawn)

  if (it < CCH_MAX_PIECE_MOVEMENTS)
  {
    // End of array prematurely
    moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}};
  }
} // End of CCH_list_pawn_moves

int CCH_list_knight_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_list_bishop_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_list_rook_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_list_queen_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_list_king_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_take_place_if_allowed(const CCH_State* state, const CCH_Move* mv, int movesAt, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  // Can't move if they have the same color
  if (!CCH_same_color(state->board[mv->from.x][mv->from.y], state->board[mv->to.x][mv->to.y]))
  {
    moves[movesAt] = *mv;
    return 1;
  }
  else
  {
    return 0;
  }
}

// Documentation in CCH_mechanics.h
int CCH_is_white(CCH_Piece p)
{
  if (p < CCH_NO_PIECE)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Documentation in CCH_mechanics.h
int CCH_same_color(CCH_Piece pa, CCH_Piece pb)
{
  return ((pa > CCH_NO_PIECE && pb > CCH_NO_PIECE)
          || (pa < CCH_NO_PIECE && pb < CCH_NO_PIECE));
}

// Documentation in CCH_mechanics.h
int CCH_is_black(CCH_Piece p)
{
  if (p > CCH_NO_PIECE)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
