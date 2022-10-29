#include "ui.hpp"
#include "gfx/colors.h"
#include "graphx.h"

void draw_button(int x, int y, const char *text, bool enabled, bool selected){
    gfx_SetColor(BLACK);
    int width = gfx_GetStringWidth(text);
    gfx_Rectangle_NoClip(x - 5 - width / 2, y, width + 10, 20);
    if(selected){
        gfx_SetColor(YELLOW);
        gfx_FillRectangle_NoClip(x - 4 - width / 2, y + 1, width + 8, 18);
    }
    if(enabled){
        gfx_SetTextFGColor(BLACK);    
    }
    else{
        gfx_SetTextFGColor(BLUE);  
    }
    gfx_PrintStringXY(text, x - width / 2, y + 5);
}

void draw_text(int x, int y, const char *text){
    gfx_SetTextFGColor(BLACK);
    int width = gfx_GetStringWidth(text);
    gfx_PrintStringXY(text, x - width / 2, y);
}

void draw_main_menu(int selectedButton, int mainMenuEntryTypes[5]){
    const char* mainMenuEntries[6] = {"LudoCE 0.0.1", "Load Game", "New Game", "Settings", "Credits", "Exit"};
    const int mainMenuEntryPos[6][2] = {{160, 20}, {160, 40}, {160, 70}, {160, 100}, {160, 130}, {160, 160}};

    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(120, 40, 80, 140);
    for(int i = 0; i < 6; i++){
        if(mainMenuEntryTypes[i] == 0){
            draw_text(mainMenuEntryPos[i][0], mainMenuEntryPos[i][1], mainMenuEntries[i]);
        }
        else if(mainMenuEntryTypes[i] == 1){
            draw_button(mainMenuEntryPos[i][0], mainMenuEntryPos[i][1], mainMenuEntries[i], true, selectedButton == i);
        }
        else if(mainMenuEntryTypes[i] == 2){
            draw_button(mainMenuEntryPos[i][0], mainMenuEntryPos[i][1], mainMenuEntries[i], false, selectedButton == i);
        }
    }
    gfx_SwapDraw();
}

void draw_credits(){
    const char *text = "Lorem ipsum dolor sit amet, ...";
    draw_text(160, 20, text);
    gfx_SwapDraw();
}

