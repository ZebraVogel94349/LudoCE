#ifndef UI_H
#define UI_H
#include <keypadc.h>

void draw_main_menu(int selectedButton, bool loadDisabled);
void draw_new_game_menu(int selectedButton, int *gameSettings);
void draw_win_screen(int winner);
void draw_credits();
int menu_up_down(int keycount, int selectedEntry, int lastEntry, kb_key_t prevkey7);
#endif