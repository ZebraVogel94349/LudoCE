#ifndef DRAW_H
#define DRAW_H

void draw_field(int x, int y, int r, int color);
void draw_field_pos(int position);
void connect_fields(int x0, int y0, int x1, int y1);
void draw_board();
void draw_player(int playerPositions[], int start, int end);
void draw_name(int playerTypes[], int newGameValues[]);
void draw_everything(int playerTypes[], int newGameValues[], int playerPositions[], int toClear, int number);
void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection);
void draw_potential_field(int selectedField, int oldField);
#endif