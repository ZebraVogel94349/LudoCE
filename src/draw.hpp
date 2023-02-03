#ifndef DRAW_H
#define DRAW_H

void draw_field_pos(int position);
void draw_board();
void draw_player(int playerPositions[], int start, int end);
void draw_everything(int playerTypes[], int playerPositions[], int toClear, int playerIndicator);
void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection);
void draw_potential_field(int selectedField, int oldField);
void start_die_animation(int n);
#endif