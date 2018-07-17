#ifndef INCLUDE_TERMINAL_INTERFACE_H_
#define INCLUDE_TERMINAL_INTERFACE_H_

#include <CCH/CCH_definitions.h>

// ANSI codes used
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_BG_BLUE "\x1b[;44"

#define CODED_CHESS_W_P "P "
#define CODED_CHESS_W_N "N "
#define CODED_CHESS_W_B "B "
#define CODED_CHESS_W_R "R "
#define CODED_CHESS_W_Q "Q "
#define CODED_CHESS_W_K "K "

#define CODED_CHESS_B_P "P "
#define CODED_CHESS_B_N "N "
#define CODED_CHESS_B_B "B "
#define CODED_CHESS_B_R "R "
#define CODED_CHESS_B_Q "Q "
#define CODED_CHESS_B_K "K "

int print_state_board(const CCH_State*);

#endif // INCLUDE_TERMINAL_INTERFACE_H_
