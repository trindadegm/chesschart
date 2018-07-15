#ifndef INCLUDE_CCH_DEFINITIONS_H_
#define INCLUDE_CCH_DEFINITIONS_H_

#define CCH_MAX_PIECE_MOVEMENTS 256

enum CCH_Piece
{
  CCH_NO_PIECE,

  CCH_WHITE_PAWN,
  CCH_WHITE_KNIGHT,
  CCH_WHITE_BISHOP,
  CCH_WHITE_ROOK,
  CCH_WHITE_QUEEN,
  CCH_WHITE_KING,  

  CCH_BLACK_PAWN,
  CCH_BLACK_KNIGHT,
  CCH_BLACK_BISHOP,
  CCH_BLACK_ROOK,
  CCH_BLACK_QUEEN,
  CCH_BLACK_KING  
};

enum CCH_Player
{
  CCH_WHITES,
  CCH_BLACKS
};

struct CCH_State
{
  enum CCH_Piece board[8][8];
  enum CCH_Player player;
  int round;
};

struct CCH_Move
{
  int from;
  int to;
};

#endif // INCLUDE_CCH_DEFINITIONS_H_
