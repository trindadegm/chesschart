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
// aval is the avaliation given to the state on this move
//
// aval is here because each move has an avaliation of whether it is a good or bad move
// for some player.
//
// It's usefulness is explained on the CCH_State documentation.
typedef struct CCH_StateMoveData
{
  CCH_Move move;
  int turn;
  struct CCH_StateMoveData* prev;
  float aval;
}CCH_StateMoveData;

// This defines the state of the game, information about rocks and king movement is mandatory
// because some movements are unavailable when some things happen on the game, even if
// the pieces are on the position required, the previous events still matter. Also, there
// may be made necessary to see all the movements required to get on this state, so those
// would be on a linked list.
//
// The stateMoveData field is used because a lot of information would be replicated in the
// search for the best move. Move related information is stored on a separated structure
// which holds which move, at which turn, and which is the avaliation given to that move
// (is it a good or bad move).
//
// So when the search tree is mounted, instead of replicating lots of 'CCH_State's,
// which are expensive bacause of the 'board' struct, and a lot of the bools
// are useful only on the calculation of newer moves, and not on the avaliation
// of situatios themselves (although indirectly important).
//
// The solution was to separate the information, so that it is possible to create
// a lighter CCH_StateMoveData tree (CCH_StateMoveData is a lighter structure
// so it can be replicated not as a big burden, CCH_State has the board matrix
// with 64 individual pieces, including empty spaces as a special piece).
//
// The avaliation will have to deal with only the important information, because it
// will keep this structure:
// 
// 1                                 CCH_StateMoveData m0__
//                               __/          |            \___
//                           ___/             |                \_
// 2     CCH_StateMoveData m1        CCH_StateMoveData m2        CCH_StateMoveData m3
//                |                           |                           |
// R         CCH_State s0                CCH_State s1                CCH_State s2
//
// Each state is a possible position after some sequence of moves, so if we analize
// the game after a move m0 here are some possible moves that cam follow that m0 move,
// those can be any number of moves, in this example we have three, m1, m2 and m3,
// and each one of them have a final state, the resulting state. The avaliation is
// made on the final state, and then it is propagated back on the tree until
// the avaliation of the move m0 is set. 
typedef struct CCH_State
{
  CCH_Piece board[8][8];
  CCH_Player player;
  bool whiteRock;
  bool whiteKingMoved;
  bool whiteKingRookMoved;
  bool whiteQueenRookMoved;
  bool blackRock;
  bool blackKingMoved;
  bool blackKingRookMoved;
  bool blackQueenRookMoved;
  CCH_StateMoveData* stateMoveData;
} CCH_State;

#endif // INCLUDE_CCH_DEFINITIONS_H_
