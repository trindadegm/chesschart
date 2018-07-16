#ifndef INCLUDE_CCH_MECHANICS_H_
#define INCLUDE_CCH_MECHANICS_H_

#include <CCH/CCH_definitions.h>

#include <assert.h>

// CCH_list_piece_moves
//
// Arguments:
// const CCH_State*   -> The board state
// int x              -> x position, of the piece coordinates (from the board)
// int y              -> y position, of the piece coordinates (from the board)
// CCH_Move[]         -> Array that contais all possible moves from the pieces
//
// Given a board state (CCH_State*) and the coordinates to find a piece
// (int x, int y) also, the address of returning by reference, the array of moves
// CCH_Move[CCH_MAX_PIECE_MOVEMENTS] will be filled with all the possible
// (VALID) moves for a piece.
//
// CCH_MAX_PIECE_MOVEMENTS is defined as the maximum size of the array: 256
//
// The array CCH_Move[CCH_MAX_PIECE_MOVEMENTS] will have an special
// invalid element in which the variables 'from' and 'to' are both {-1, -1}
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
//    (CCH_State*) is not NULL or if the move array
//    (CCH_Move[CCH_MAX_PIECE_MOVEMENTS]) is an adequate reference.
//
//    When the position selected hold CCH_NO_PIECE, it will do NOTHING,
//    meaning that the movement array will be unmodified and possible
//    contain just memmory trash.
//
// Return values (int)
// 0: Success.
// 1: Warning: There was an attempt to move no piece (CCH_NO_PIECE: Piece)
// 2: Warning: There is an invalid piece on the board state (CCH_State*) or
//    the coordinates (int x, int y) to find a piece are out of bounds.
int CCH_list_piece_moves(const CCH_State*, int x, int y, CCH_Move[CCH_MAX_PIECE_MOVEMENTS]);

// CCH_is_black
//
// Arguments:
// CCH_Piece
//  -> The piece to be analized
//
// Returns 1 if a piece IS BLACK.
// This information is quite useful on lots of procedures, it gives crucial information,
// so it was placed in a procedure of its own.
//
// NOTES:
//    Be careful when using this method to know wether a piece is WHITE, that is because
//    if 'p' equals 'CCH_NO_PIECE', this will still return 0, because it is not BLACK,
//    even thought it is not WHITE either.
//
// Return values (int)
// 0: The piece (CCH_Piece p) is not BLACK
// 1: The piece (CCH_Piece p) is BLACK
int CCH_is_black(CCH_Piece p);

// CCH_is_white
//
// Arguments:
// CCH_Piece
//  -> The piece to be analized
//
// Returns 1 if a piece IS WHITE
// This information is quite useful on lots of procedures, it gives crucial information,
// so it was placed in a procedure of its own.
//
// NOTES:
//    Be careful when using this method to know wether a piece is BLACK, that is because
//    if 'p' equals 'CCH_NO_PIECE', this will still return 0, because it is not WHITE,
//    even thought it is not BLACK either.
//
// Return values (int)
// 0: The piece (CCH_Piece p) is not WHITE
// 1: The piece (CCH_Piece p) is WHITE
int CCH_is_white(CCH_Piece p);

// CCH_same_color
//
// Arguments:
// CCH_Piece pa
//  -> First piece to be compared
// CCH_Piece pb
//  -> Second piece to be compared
//
// Returns 1 if 'pa' (CCH_Piece) and 'pb' (CCH_Piece) are of the same color, that means,
// if BOTH are white or BOTH are black.
//
// NOTES:
//    If either 'pa' (CCH_Piece) or 'pb' (CCH_Piece) (or both) are equal to 'CCH_NO_PIECE',
//    this procedure will return 0.
//
// Return values (int)
// 1: The pieces (CCH_Piece pa and CCH_Piece pb) are of the same color.
// 0: The pieces (CCH_Piece pa and CCH_Piece pb) are of different colors
//    OR either one (or both) of them is 'CCH_NO_PIECE'
int CCH_same_color(CCH_Piece pa, CCH_Piece pb);

#endif // INCLUDE_CCH_MECHANICS_H_
