#ifndef GAME_H
#define GAME_H

int get_color(int playerNumber, int boardType);
int occupied_by(int position, int playerPositions[], int boardType);
int move_n_fields(int pieceColor, int position, int n, int boardType);
int check_for_order(int playerPositions[], int pieceColor, int figureCount, int boardType);
bool is_player_movable(int playerPositions[], int pieceColor, int selectedPlayer, int n, int figureCount, int boardType);
int *move_player(int playerPositions[], int pieceColor, int selectedPlayer, int n, int boardType);
int *move_enemy(int playerPositions[], int pieceColor, int n, int botStrength, int figureCount, int boardType);
int check_for_win(int playerPositions[], int figureCount, int boardType);
#endif