#include "ui.hpp"
#include "gfx/colors.h"
#include "graphx.h"

void draw_button(int x, int y, const char *text, bool enabled, bool selected){
    gfx_SetColor(BLACK);
    int width = gfx_GetStringWidth(text);
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
    gfx_PrintStringXY(text, x - width / 2, y + 6);
}

void draw_selection_button(int x, int y, const int number, const char *text, bool enabled, bool selected){
    gfx_SetColor(BLACK);
    int width = gfx_GetStringWidth("0");
    if(number != -1){
        gfx_SetTextXY(x - width / 2, y);
        gfx_PrintInt(number, 1);
    }else{
        width = gfx_GetStringWidth(text);
        gfx_PrintStringXY(text, x - width / 2, y);
    }
    gfx_FillTriangle_NoClip(x - 25 - width / 2, y + 3, x - 15 - width / 2, y, x - 15 - width / 2, y + 6);
    gfx_FillTriangle_NoClip(x + 25 + width / 2, y + 3, x + 15 + width / 2, y, x + 15 + width / 2, y + 6);
    if(selected){
        gfx_SetColor(ORANGE);
        gfx_Rectangle_NoClip(x - 25 - width / 2, y - 5, width + 50, 16);
    }
}

void draw_text(int x, int y, const char *text){
    gfx_SetTextFGColor(BLACK);
    int width = gfx_GetStringWidth(text);
    gfx_PrintStringXY(text, x - width / 2, y);
}

void draw_main_menu(int selectedButton, int *mainMenuEntryTypes){
    const char* mainMenuEntries[6] = {"LudoCE 0.0.1", "Load Game", "New Game", "Settings", "Credits", "Exit"};
    const int mainMenuEntryPos[6][2] = {{160, 20}, {160, 40}, {160, 70}, {160, 100}, {160, 130}, {160, 160}};

    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(0, 0, 320, 240);
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

void draw_new_game_menu(int selectedButton, int *newGameValues){
    const char* newGameEntries[7] = {"Player Count", "Player", "Bots", "Figure Count", "Bot Strength", "Colors", "Start"};
    const char* botStrengthValues[3] = {"Easy", "Normal", "Hard"};
    const int newGameEntryPos[7][2] = {{160, 20}, {128, 70}, {192, 70}, {108, 120}, {212, 120}, {160, 170}, {160, 200}};
    const int newGameEntryTypes[7] = {0, 0, 0, 0, 0, 1, 1}; // 0 = selection button, 1 = button

    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(0, 0, 320, 240);
    for(int i = 0; i < sizeof(newGameEntries); i++){
        if(newGameEntryTypes[i] == 0 && i < 4){
            draw_text(newGameEntryPos[i][0], newGameEntryPos[i][1], newGameEntries[i]);
            draw_selection_button(newGameEntryPos[i][0], newGameEntryPos[i][1] + 20, newGameValues[i], "", true, selectedButton == i + 1);
        }
        else if(i == 4){
            draw_text(newGameEntryPos[i][0], newGameEntryPos[i][1], newGameEntries[i]);
            draw_selection_button(newGameEntryPos[i][0], newGameEntryPos[i][1] + 20, -1, botStrengthValues[newGameValues[4] - 1], true, selectedButton == i + 1);
        }
        else if(newGameEntryTypes[i] == 1){
            draw_button(newGameEntryPos[i][0], newGameEntryPos[i][1], newGameEntries[i], true, selectedButton == i + 1);
        }
    }
    gfx_SwapDraw();
}

void draw_credits(){
    const char *text = "Lorem ipsum dolor sit amet, ...";
    draw_text(160, 20, text);
    gfx_SwapDraw();
}

