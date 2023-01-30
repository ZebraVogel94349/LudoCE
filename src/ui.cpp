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

void draw_selection_button(int x, int y, const char* label, const int number, const char *text, bool selected, bool enabled){
    int width = gfx_GetStringWidth("0");
    gfx_SetTextFGColor(BLACK);
    if(!enabled){
        gfx_SetTextFGColor(GREY);
    }
    if(number > -1){
        gfx_SetTextXY(x - width / 2, y);
        gfx_PrintInt(number, 1);
    }
    else{
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
    if(number <= -2){
        gfx_SetColor(BLACK);
        gfx_Rectangle_NoClip(x - 21, y - 21, 42, 12);
        gfx_SetColor(number * -1);
        gfx_FillRectangle_NoClip(x - 20 , y - 20, 40, 10);
    }
}

void draw_main_menu(int selectedButton, bool loadDisabled){
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(120, 40, 80, 140);
    gfx_PrintStringXY("LudoCE 0.0.1", 160 - gfx_GetStringWidth("LudoCE 0.0.1") / 2, 5);
    draw_button(160, 40, "Load Game", loadDisabled, selectedButton == 0);
    draw_button(160, 70, "New Game", true, selectedButton == 1);
    draw_button(160, 100, "Settings", true, selectedButton == 2);
    draw_button(160, 130, "About", true, selectedButton == 3);
    draw_button(160, 160, "Exit", true, selectedButton == 4);
    gfx_SwapDraw();
}

void draw_new_game_menu(int selectedButton, int *gameSettings, int*playerTypes){
    const char* botStrengthValues[3] = {"Easy", "Normal", "Hard"};
    const char* playerNames[3] = {"Player", "CPU", "Disabled"};
    const char* boardNames[2] = {"4 Players", "6 Players"};
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(50, 0, 220, 235);

    draw_selection_button(160, 20, "Board", -1, boardNames[gameSettings[0]], selectedButton == 0, true);
    draw_selection_button(160, 50, "Figure Count", gameSettings[1] + 1, "", selectedButton == 1, true);
    draw_selection_button(160, 80, "Bot Strength", -1, botStrengthValues[gameSettings[2]], selectedButton == 2, true);

    draw_selection_button(105, 120, "", -2, playerNames[playerTypes[0]], selectedButton == 3, true);
    draw_selection_button(215, 120, "", -3, playerNames[playerTypes[1]], selectedButton == 4, true);
    draw_selection_button(105, 160, "", -4, playerNames[playerTypes[2]], selectedButton == 5, true);
    draw_selection_button(215, 160, "", -5, playerNames[playerTypes[3]], selectedButton == 6, true);
    draw_selection_button(105, 200, "", -6, playerNames[playerTypes[4]], selectedButton == 7, gameSettings[0] == 1);
    draw_selection_button(215, 200, "", -7, playerNames[playerTypes[5]], selectedButton == 8, gameSettings[0] == 1);

    draw_button(160, 215, "Start", gameSettings[3] > 0, selectedButton == 9);
    gfx_SwapDraw();
}

void draw_win_screen(int winner){
    const char* colors[6] = {"Blue", "Red", "Yellow", "Green, Purple, Cyan"};
    gfx_FillScreen(BACKGROUND_YELLOW);
    gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" wins!")) / 2, 90);
    gfx_PrintString(colors[winner - 2]);
    gfx_PrintString(" wins!");
    gfx_PrintStringXY("Press [del] to return to the main menu", 160 - gfx_GetStringWidth("Press [del] to return to the main menu") / 2, 130);
    gfx_SwapDraw();
}

void draw_about(int page){
    const char *p1l1 = "Lorem ipsum dolor sit amet, ...";
    const char *p2l1 = "consetetur sadipscing elitr, sed diam ...";
    const char *p3l1 = "nonumy eirmod tempor invidunt ut labore ...";
    gfx_SetTextXY(295, 5);
    gfx_PrintInt(page + 1, 1);
    gfx_PrintString("/3");
    if(page != 0){
        gfx_PrintStringXY("\x1e", 5, 5);
    }
    if(page != 2){
        gfx_PrintStringXY("\x1f", 5, 230);
    }

    if(page == 0){
        gfx_PrintStringXY(p1l1, 5, 20);
    }
    else if(page == 1){
        gfx_PrintStringXY(p2l1, 5, 20);
    }
    else if(page == 2){
        gfx_PrintStringXY(p3l1, 5, 20);
    }
    
    gfx_SwapDraw();
}

int menu_up_down(int keycount, int selectedEntry, int lastEntry, kb_key_t prevkey7){
    if(kb_Data[7] == kb_Down && (prevkey7 != kb_Down || keycount % 10 == 9)){
        selectedEntry = (selectedEntry + 1) % (lastEntry + 1);
    }
    if(kb_Data[7] == kb_Up && (prevkey7 != kb_Up || keycount % 10 == 9)){
        selectedEntry = (selectedEntry + lastEntry) % (lastEntry + 1);
    }
    return selectedEntry;
}