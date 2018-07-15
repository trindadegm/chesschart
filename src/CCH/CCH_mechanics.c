#include <CCH/CCH_mechanics.h>

// These functions are special cases of the function CCH_move_piece, and are used on
// the function CCH_move_piece, that means they have similar jobs, and therefore
// share almost the same documentation.
//
// As each piece has different moves, different procedures were required to move
// each piece.
int CCH_move_pawn(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_move_knight(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_move_bishop(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_move_rook(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_move_queen(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);
int CCH_move_king(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);

// Documentation in CCH_mechanics.h
int CCH_move_piece(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
  enum CCH_Piece piece = state->board[x][y];

  // Moving is different for each piece
  switch (piece)
  {
    case CCH_WHITE_PAWN:
    case CCH_BLACK_PAWN:
      return CCH_move_pawn(state, x, y, moves);
      break;
    case CCH_WHITE_KNIGHT:
    case CCH_BLACK_KNIGHT:
      return CCH_move_knight(state, x, y, moves);
      break;
    case CCH_WHITE_BISHOP:
    case CCH_BLACK_BISHOP:
      return CCH_move_bishop(state, x, y, moves);
      break;
    case CCH_WHITE_ROOK:
    case CCH_BLACK_ROOK:
      return CCH_move_rook(state, x, y, moves);
      break;
    case CCH_WHITE_QUEEN:
    case CCH_BLACK_QUEEN:
      return CCH_move_queen(state, x, y, moves);
      break;
    case CCH_WHITE_KING:
    case CCH_BLACK_KING:
      return CCH_move_king(state, x, y, moves);
      break;
    case CCH_NO_PIECE: // Can't move no piece
      return 1; // A warning, very light one, it it trying to move nothing
      break;
    default:    // Invalid piece found, may be dangerous
      return 2; // A warning
  }
}

int CCH_move_pawn(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_move_knight(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_move_bishop(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_move_rook(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_move_queen(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}

int CCH_move_king(struct CCH_State* state, int x, int y, struct CCH_Move moves[CCH_MAX_PIECE_MOVEMENTS])
{
}
