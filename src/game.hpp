#ifndef GAME_H
#define GAME_H

int get_color(int playerNumber);
int occupied_by(int position, int playerPositions[]);
int move_n_fields(int pieceColor, int position, int n);
int *throw_out(int playerPositions[], int player, int oldPosition, int n);
int check_for_order(int playerPositions[], int pieceColor);
bool all_out(int playerPositions[], int playerNumberStart, int hm_pos);
bool is_player_movable(int playerPositions[], int pieceColor, int selectedPlayer, int n);
int *move_player(int playerPositions[], int pieceColor, int selectedPlayer, int n);
int *move_enemy(int playerPositions[], int pieceColor, int n, int botStrength);
int check_for_win(int playerPositions[]);
#endif