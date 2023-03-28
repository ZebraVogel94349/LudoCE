#ifndef DRAW_H
#define DRAW_H

void draw_field_pos(int position, int boardType);
void draw_board(int boardType);
void draw_player(int playerPositions[], int start, int end, int boardType);
void draw_everything(int playerTypes[], int playerPositions[], int toClear, int playerIndicator, int boardType);
void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection, int boardType);
void draw_potential_field(int selectedField, int oldField, int boardType);
void start_die_animation(int n);
#endif