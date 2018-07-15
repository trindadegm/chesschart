#ifndef INCLUDE_CCH_MECHANICS_H_
#define INCLUDE_CCH_MECHANICS_H_

#include <CCH/CCH_definitions.h>

// Move piece
//
// Given a board state (struct CCH_State*) and the coordinates to find a piece
// (int x, int Y) also, the address of returning by reference, the array of moves
// struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS] will be filled with all the possible
// (VALID) moves for a piece.
//
// The array struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS] will have an special
// invalid element in which the struct variables 'from' and 'to' are both -1.
// That will mean the array was finished prematurely, and should NOT be further
// readed, as the contents of the rest of the positions is undefined.
//
// When the array is full, the special invalid element is NOT on the array,
// meaning that all elements are useful, this means the special invalid
// element is just a way to end the array before it is full.
//
// NOTES:
//    This procedure WILL NOT check wether or not it's arguments are valid,
//    take care to always be sure the coordinates (int x, int y) are in bounds
//    (x and y are bigger or equal to 0 and smaller than 8), the board state
//    (struct CCH_State*) is not NULL or if the move array
//    (struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]) is an adequate reference.
//
// Return values (int)
// 0: Success.
// 1: Warning: There was an attempt to move no piece (CCH_NO_PIECE: enum Piece)
// 2: Warning: There is an invalid piece on the board state (struct CCH_State*) or
//    the coordinates (int x, int y) to find a piece are out of bounds.
int CCH_move_piece(struct CCH_State*, int x, int y, struct CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);

#endif // INCLUDE_CCH_MECHANICS_H_
