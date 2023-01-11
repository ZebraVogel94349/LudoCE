#include <graphx.h>
#include <keypadc.h>
#include "ui.hpp"
#include "gfx/colors.h"

void draw_button(int x, int y, const char *label, bool enabled, bool selected){
    gfx_SetColor(BLACK);
    int width = gfx_GetStringWidth(label);
    gfx_Rectangle_NoClip(x - 5 - width / 2, y, width + 10, 20);
    if(selected){
        gfx_SetColor(ORANGE);
        gfx_FillRectangle_NoClip(x - 4 - width / 2, y + 1, width + 8, 18);
    }
    if(enabled){
        gfx_SetTextFGColor(BLACK);    
    }
    else{
        gfx_SetTextFGColor(GREY);  
    }
    gfx_PrintStringXY(label, x - width / 2, y + 6);
}

void draw_selection_button(int x, int y, const char* label, const int number, const char *text, bool selected){
    int width = gfx_GetStringWidth("0");
    if(number != -1){
        gfx_SetTextXY(x - width / 2, y);
        gfx_PrintInt(number, 1);
    }else{
        width = gfx_GetStringWidth(text);
        gfx_PrintStringXY(text, x - width / 2, y);
    }
    gfx_PrintStringXY("\x11", x - 13 - width / 2, y);
    gfx_PrintStringXY("\x10", x + width / 2 + 5, y);
    if(selected){
        gfx_SetColor(ORANGE);
        gfx_Rectangle_NoClip(x - 25 - width / 2, y - 5, width + 50, 16);
    }
    gfx_PrintStringXY(label, x - gfx_GetStringWidth(label) / 2, y - 15);
}

void draw_main_menu(int selectedButton, bool loadDisabled){
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(120, 40, 80, 140);
    gfx_PrintStringXY("LudoCE 0.0.1", 160 - gfx_GetStringWidth("LudoCE 0.0.1") / 2, 5);
    draw_button(160, 40, "Load Game", loadDisabled, selectedButton == 0);
    draw_button(160, 70, "New Game", true, selectedButton == 1);
    draw_button(160, 100, "Settings", true, selectedButton == 2);
    draw_button(160, 130, "Credits", true, selectedButton == 3);
    draw_button(160, 160, "Exit", true, selectedButton == 4);
    gfx_SwapDraw();
}

void draw_new_game_menu(int selectedButton, int *gameSettings){
    const char* botStrengthValues[3] = {"Easy", "Normal", "Hard"};
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(0, 0, 320, 240);
    draw_selection_button(160, 40, "Board", gameSettings[0], "", selectedButton == 0);
    draw_selection_button(128, 90, "Player", gameSettings[1], "", selectedButton == 1);
    draw_selection_button(192, 90, "Bots", gameSettings[2], "", selectedButton == 2);
    draw_selection_button(108, 140, "Figure Count", gameSettings[3], "", selectedButton == 3);
    draw_selection_button(212, 140, "Bot Strength", -1, botStrengthValues[gameSettings[4]], selectedButton == 4);
    draw_button(160, 170, "Colors", true, selectedButton == 5);
    draw_button(160, 200, "Start", true, selectedButton == 6);
    gfx_SwapDraw();
}

void draw_win_screen(int winner){
    const char* colors[4] = {"Blue", "Red", "Yellow", "Green"};
    gfx_FillScreen(BACKGROUND_YELLOW);
    gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" wins!")) / 2, 90);
    gfx_PrintString(colors[winner - 2]);
    gfx_PrintString(" wins!");
    gfx_PrintStringXY("Press [del] to return to the main menu", 160 - gfx_GetStringWidth("Press [del] to return to the main menu") / 2, 130);
    gfx_SwapDraw();
}

void draw_credits(){
    const char *text = "Lorem ipsum dolor sit amet, ...";
    gfx_PrintStringXY(text, 160 - gfx_GetStringWidth(text) / 2, 20);
    gfx_SwapDraw();
}

int menu_up_down(int keycount, int selectedEntry, int lastEntry, kb_key_t prevkey7){
    if(kb_Data[7] == kb_Down && (prevkey7 != kb_Down || keycount % 10 == 9)){
        if(selectedEntry == lastEntry){
            selectedEntry = 0;
        }
        else{
            selectedEntry++;
        }
    }
    if(kb_Data[7] == kb_Up && (prevkey7 != kb_Up || keycount % 10 == 9)){
        if(selectedEntry == 0){
            selectedEntry = lastEntry;
        }
        else{
            selectedEntry--;
        }
    }
    return selectedEntry;
}