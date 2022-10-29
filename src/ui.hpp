#ifndef UI_H
#define UI_H

void draw_button(int x, int y, const char *text, bool enabled, bool selected);
void draw_main_menu(int selectedButton, int mainMenuEntryTypes[5]);
void draw_credits();

#endif