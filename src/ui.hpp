#ifndef UI_H
#define UI_H
#include <keypadc.h>

void draw_button(int x, int y, const char *text, bool enabled, bool selected);
void draw_selection_button(int x, int y, const int *label, const int number, const char *text, bool selected);
void draw_main_menu(int selectedButton, bool loadDisabled);
void draw_new_game_menu(int selectedButton, int *newGameValues);
void draw_credits();
int menu_up_down(int keycount, int selectedEntry, int lastEntry, kb_key_t prevkey7);
#endif