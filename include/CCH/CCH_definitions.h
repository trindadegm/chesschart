#ifndef INCLUDE_CCH_DEFINITIONS_H_
#define INCLUDE_CCH_DEFINITIONS_H_

#define CCH_MAX_PIECE_MOVEMENTS 27

#include <stdbool.h>

// This is defined for easy modifications later
typedef short CCH_Move_Coordinate;

// This defines all the possible values of a CHESS PIECE,
// assuming that they will not change anytime soon.
typedef enum CCH_Piece
{
  // All white pieces
  CCH_WHITE_PAWN,
  CCH_WHITE_KNIGHT,
  CCH_WHITE_BISHOP,
  CCH_WHITE_ROOK,
  CCH_WHITE_QUEEN,
  CCH_WHITE_KING,  

  // No piece, this represents an empty space on the board, it is placed on the middle, so that given
  // any piece other (VALID!) piece, comparing it to this will give enough information to tell if
  // it is white or black (piece < CCH_NO_PIECE means piece is white, piece > CCH_NO_PIECE means piece
  // is black).
  CCH_NO_PIECE,

  // All black pieces
  CCH_BLACK_PAWN,
  CCH_BLACK_KNIGHT,
  CCH_BLACK_BISHOP,
  CCH_BLACK_ROOK,
  CCH_BLACK_QUEEN,
  CCH_BLACK_KING  
} CCH_Piece;

// This is used when we need to store information about which player we are talking about
typedef enum CCH_Player
{
  CCH_WHITES,
  CCH_BLACKS
} CCH_Player;

// This defines a point on the board, the x coordinate corresponds to the letter on the
// standart chess notation (the column) and the y corresponds to the number on the
// standart chess notation (the row). They are defined as CCH_Move_Coordinate, which is
// a custom type, defined previously, so that the actual size of this type is disregarded.
//
// CCH_Move_Coordinate IS INTEGER though (either char, int or any other of them).
typedef struct CCH_Point
{
  CCH_Move_Coordinate x;
  CCH_Move_Coordinate y;
} CCH_Point;

// This defines a movement of a piece, also, it is used for captures, meaning a move from an
// ally piece to the position of an enemy piece is a capture. The move is made out of to
// points, respectively, the point from the start of the movement, to the point of the
// end of the movement (from and to).
typedef struct CCH_Move
{
  CCH_Point from;
  CCH_Point to;
} CCH_Move;

// This defines a linked list of moves
typedef struct CCH_Move_List
{
  CCH_Move move;
  struct CCH_Move_List* next;
}CCH_Move_List;

// This defines the state of the game, information about rocks and king movement is mandatory
// because some movements are unavailable when some things happen on the game, even if
// the pieces are on the position required, the previous events still matter. Also, there
// may be made necessary to see all the movements required to get on this state, so those
// would be on a linked list.
//
// The move linked list makes the existence of the bools for rock and king movement redundant,
// as the list could be used to track back the events and discover any event of the game. But
// that would be unneficient so it was disregarded. The bools are there to make getting the
// information about the events much quicker.
//
// On the prevMvList, the next attribute is actually a pointer to the previous move, do not
// be confused (if possible).
typedef struct CCH_State
{
  CCH_Piece board[8][8];
  CCH_Player player;
  int round;
  bool whiteRock;
  bool whiteKingMoved;
  bool blackRock;
  bool blackKingMoved;
  CCH_Move_List prevMvList;
} CCH_State;

#endif // INCLUDE_CCH_DEFINITIONS_H_
