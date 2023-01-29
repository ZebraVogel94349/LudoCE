#ifndef UI_H
#define UI_H
#include <keypadc.h>

void draw_main_menu(int selectedButton, bool loadDisabled);
void draw_new_game_menu(int selectedButton, int *gameSettingsm, int *playerTypes);
void draw_win_screen(int winner);
void draw_about(int page);
int menu_up_down(int keycount, int selectedEntry, int lastEntry, kb_key_t prevkey7);
#endif