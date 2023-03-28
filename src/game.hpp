#ifndef GAME_H
#define GAME_H

int get_color(int playerNumber, const int* BOARD_DATA);
int occupied_by(int position, int playerPositions[], const int* BOARD_DATA);
int move_n_fields(int pieceColor, int position, int n, const int* BOARD_DATA, const int (*BOARD_COLOR_DATA)[5]);
int check_for_order(int playerPositions[], int pieceColor, int figureCount, const int* BOARD_DATA, const int (*BOARD_COLOR_DATA)[5]);
bool is_player_movable(int playerPositions[], int pieceColor, int selectedPlayer, int n, int figureCount, const int* BOARD_DATA, const int (*BOARD_COLOR_DATA)[5]);
int *move_player(int playerPositions[], int pieceColor, int selectedPlayer, int n, const int* BOARD_DATA, const int (*BOARD_COLOR_DATA)[5]);
int *move_enemy(int playerPositions[], int pieceColor, int n, int botStrength, int figureCount, const int* BOARD_DATA, const int (*BOARD_COLOR_DATA)[5]);
int check_for_win(int playerPositions[], int figureCount, const int* BOARD_DATA);
#endif