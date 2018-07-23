#ifndef INCLUDE_CLI_TERMINAL_INTERFACE_H_
#define INCLUDE_CLI_TERMINAL_INTERFACE_H_

#include <CCH/CCH_definitions.h>

// These define the characters for each piece, the letters 'X' in 
// CODED_CHESS_'X' is the one used on english chess notation (the standart
// engligh chess notation), the string ones may be changed to any
// other prefered notation, but the space character should be there to
// separate the characters on the board.
#define CODED_CHESS_P "P "
#define CODED_CHESS_N "N "
#define CODED_CHESS_B "B "
#define CODED_CHESS_R "R "
#define CODED_CHESS_Q "Q "
#define CODED_CHESS_K "K "

#define COMMAND_ARRAY_LENGTH 20
#define COMMAND_MAX_LENGTH 128

// print_state_board
//
// Uses ANSI colors to print a board on the terminal
int CLI_print_state_board(const CCH_State*);

int CLI_interface_play(const CCH_State*, CCH_Player);

#endif // INCLUDE_CLI_TERMINAL_INTERFACE_H_
