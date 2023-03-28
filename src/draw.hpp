#ifndef DRAW_H
#define DRAW_H

void draw_field_pos(int position, const int (*BOARD)[3], const int* BOARD_DATA);
void draw_board(const int (*BOARD)[3], const int* BOARD_DATA);
void draw_player(int playerPositions[], int start, int end, const int (*BOARD)[3], const int* BOARD_DATA);
void draw_everything(int playerTypes[], int playerPositions[], int toClear, int playerIndicator, const int (*BOARD)[3], const int* BOARD_DATA, const int (*BOARD_PLAYER_NAMING)[2], int boardType);
void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection, const int (*BOARD)[3], const int* BOARD_DATA);
void draw_potential_field(int selectedField, int oldField, const int (*BOARD)[3], const int* BOARD_DATA);
void start_die_animation(int n);
#endif