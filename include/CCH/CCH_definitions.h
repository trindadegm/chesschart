#ifndef INCLUDE_CCH_DEFINITIONS_H_
#define INCLUDE_CCH_DEFINITIONS_H_

#define CCH_MAX_PIECE_MOVEMENTS 27

typedef enum CCH_Piece
{
  CCH_WHITE_PAWN,
  CCH_WHITE_KNIGHT,
  CCH_WHITE_BISHOP,
  CCH_WHITE_ROOK,
  CCH_WHITE_QUEEN,
  CCH_WHITE_KING,  

  CCH_NO_PIECE,

  CCH_BLACK_PAWN,
  CCH_BLACK_KNIGHT,
  CCH_BLACK_BISHOP,
  CCH_BLACK_ROOK,
  CCH_BLACK_QUEEN,
  CCH_BLACK_KING  
} CCH_Piece;

typedef enum CCH_Player
{
  CCH_WHITES,
  CCH_BLACKS
} CCH_Player;

typedef struct CCH_State
{
  CCH_Piece board[8][8];
  CCH_Player player;
  int round;
} CCH_State;

typedef struct CCH_Point
{
  int x;
  int y;
} CCH_Point;

typedef struct CCH_Move
{
  CCH_Point from;
  CCH_Point to;
} CCH_Move;

#endif // INCLUDE_CCH_DEFINITIONS_H_
