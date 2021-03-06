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


// TODO ADD EN PASSANT CAPTURE ON PANW MOVES!
// TODO ADD ROCK MOVEMENT ON KING MOVES!

int CCH_is_position_inbounds(CCH_Point pos);
int CCH_take_place_if_allowed(const CCH_State*, const CCH_Move*, int movesAt, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_keep_move_in_line(const CCH_State*, int x, int y, int mvx, int mvy, int movesAt, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_keep_diagonal_move(const CCH_State*, int x, int y, int movesAt, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_keep_horizontal_move(const CCH_State*, int x, int y, int movesAt, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);

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

// Documentation on the heading of this file
int CCH_list_pawn_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  int it = 0;
  CCH_Move mv;

  assert((x > -1 && y > -1) && (x < 8 && y < 8)); // ASSERTION

  if (CCH_is_white(state->board[x][y])) // If the pawn is white, then
  {
    mv = (CCH_Move) {{x, y}, {x, y+1}};
    if (mv.to.y < 8) // If pawn is moving INBOUNDS one step
    { 
      // FOWARD MOVING
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
    } // End of if pawn is moving INBOUNDS one step
  } // End of if it is a white pawn
  else // It is a black pawn (if it is a pawn it can't be no piece)
  {
    mv = (CCH_Move) {{x, y}, {x, y-1}};
    if (mv.to.y > -1) // If pawn is moving INBOUNDS one step
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
    } // End of if pawn is moving INBOUNDS one step
  } // End of else (it is a black pawn)

  // End of array prematurely (pawn can't move that much at all, so it WILL end prematurely)
  moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}};

  return 0;
} // End of CCH_list_pawn_moves

// Documentation on the heading of this file
int CCH_list_knight_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  // The knight can move to a maximum of 8 points. those could be put as:
  //  -> x+2 and y+1
  //  -> x+1 and y+2
  //  -> x+2 and y-1
  //  -> x+1 and y-2
  //  -> x-2 and y+1
  //  -> x-1 and y+2
  //  -> x-2 and y-1
  //  -> x-1 and y-2
  //
  // This explains everything about the logic of this procedure.
  // Take a board and try it if you have any doubts.
  int it = 0;
  CCH_Move mv = (CCH_Move) {{x, y}, {x+2, y+1}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x+1, y+2}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x+2, y-1}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x+1, y-2}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x-2, y+1}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x-1, y+2}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x-2, y-1}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }
  mv = (CCH_Move) {{x, y}, {x-1, y-2}};
  if (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}))
  {
    it += CCH_take_place_if_allowed(state, &mv, it, moves);
  }

  moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}};
  return 0;
}

// Documentation on the heading of this file
int CCH_list_bishop_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  int it = 0;
  // Bishop moves diagonaly
  it = CCH_keep_diagonal_move(state, x, y, it, moves);

  moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}};

  return 0;
}

// Documentation on the heading of this file
int CCH_list_rook_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  int it = 0;
  // Rook moves horizontaly
  it = CCH_keep_horizontal_move(state, x, y, it, moves);

  moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}};

  return 0;
}

// Documentation on the heading of this file
int CCH_list_queen_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  int it = 0;
  // Queen moves horizontaly and diagonaly
  it = CCH_keep_horizontal_move(state, x, y, it, moves);
  it = CCH_keep_diagonal_move(state, x, y, it, moves);

  // If it didn't fill the array
  if (it < CCH_MAX_PIECE_MOVEMENTS)
  {
    moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}};
  }

  return 0;
}

// Documentation on the heading of this file
int CCH_list_king_moves(const CCH_State* state, int x, int y, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  int it = 0;
  CCH_Move mv = (CCH_Move) {{x, y}, {0, 0}};

  // For all the 9 squares, 8 aroung the king (and the king'ssquare)
  for (int i = x-1; i < x+2; ++i)
  {
    for (int j = y-1; j < y+2; ++j)
    {
      if (i != x || j != y) // Ok, disregard the kings's square
      {
        // Try moving there
        mv.to.x = i;
        mv.to.y = j;
        if (CCH_is_position_inbounds((CCH_Point) {i, j}))
        {
          it += CCH_take_place_if_allowed(state, &mv, it, moves);
        }
      } // End of if it is not on king's square
    } // End of second for
  } // End of first for

  moves[it] = (CCH_Move) {{-1, -1}, {-1, -1}}; // End move array
  return 0;
}

// Documentation on the heading of this file
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

// Documentation on the heading of this file
int CCH_is_position_inbounds(CCH_Point pos)
{
  return (pos.x > -1 && pos.x < 8 && pos.y > -1 && pos.y < 8);
}

// Documentation on the heading of this file
int CCH_keep_move_in_line(const CCH_State* state, int x, int y, int mvx, int mvy, int movesAt,
                          CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  CCH_Move mv = (CCH_Move) {{x, y}, {x+mvx, x+mvy}};
  bool noCapture = true;
  while (CCH_is_position_inbounds((CCH_Point) {mv.to.x, mv.to.y}) && noCapture)
  {
    int place = CCH_take_place_if_allowed(state, &mv, movesAt, moves);
    if (!CCH_same_color(state->board[x][y], state->board[mv.to.x][mv.to.y]) && state->board[mv.to.x][mv.to.y] != CCH_NO_PIECE)
    {
      noCapture = false; // Bacause the move is a capture now
    }

    if (place == 0) // Couldn't move
    {
      break;
    }
    else
    {
      ++movesAt;
      mv.to.x += mvx;
      mv.to.y += mvy;
    }
  }
  return movesAt;
}

// Documentation on the heading of this file
int CCH_keep_diagonal_move(const CCH_State* state, int x, int y, int movesAt, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  // Diagonaly move the four ways
  movesAt = CCH_keep_move_in_line(state, x, y, +1, +1, movesAt, moves);
  movesAt = CCH_keep_move_in_line(state, x, y, +1, -1, movesAt, moves);
  movesAt = CCH_keep_move_in_line(state, x, y, -1, +1, movesAt, moves);
  movesAt = CCH_keep_move_in_line(state, x, y, -1, -1, movesAt, moves);

  return movesAt;
}

// Documentation on the heading of this file
int CCH_keep_horizontal_move(const CCH_State* state, int x, int y, int movesAt, CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  // Horizontaly move the four ways
  movesAt = CCH_keep_move_in_line(state, x, y, +1, 0, movesAt, moves);
  movesAt = CCH_keep_move_in_line(state, x, y, -1, 0, movesAt, moves);
  movesAt = CCH_keep_move_in_line(state, x, y, 0, +1, movesAt, moves);
  movesAt = CCH_keep_move_in_line(state, x, y, 0, -1, movesAt, moves);

  return movesAt;
}

// Documentation in CCH_mechanics.h
int CCH_same_color(CCH_Piece pa, CCH_Piece pb)
{
  return ((pa > CCH_NO_PIECE && pb > CCH_NO_PIECE)
          || (pa < CCH_NO_PIECE && pb < CCH_NO_PIECE));
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
