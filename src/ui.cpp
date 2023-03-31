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
    draw_button(160, 75, "New Game", true, selectedButton == 1);
    draw_button(160, 110, "About", true, selectedButton == 2);
    draw_button(160, 145, "Exit", true, selectedButton == 3);
    gfx_BlitBuffer();
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
    gfx_BlitBuffer();
}

void draw_win_screen(int winner, int place, int lastPlace){
    const char* colors[6] = {"Blue", "Red", "Yellow", "Green", "Purple", "Cyan"};
    gfx_FillScreen(BACKGROUND_YELLOW);
    if(place == 1){
        gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" wins!")) / 2, 70);
        gfx_PrintString(colors[winner - 2]);
        gfx_PrintString(" wins!");
    }
    else if(place == 2){
        gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" is 2nd!")) / 2, 70);
        gfx_PrintString(colors[winner - 2]);
        gfx_PrintString(" is 2nd!");
    }
    else if(place == 3){
        gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" is 3rd!")) / 2, 70);
        gfx_PrintString(colors[winner - 2]);
        gfx_PrintString(" is 3rd!");
    }
    else if(place == 4){
        gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" is 4th")) / 2, 70);
        gfx_PrintString(colors[winner - 2]);
        gfx_PrintString(" is 4th");
    }
    else if(place == 5){
        gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[winner - 2]) + gfx_GetStringWidth(" is 5th")) / 2, 70);
        gfx_PrintString(colors[winner - 2]);
        gfx_PrintString(" is 5th");
    }

    if(lastPlace > -1){
        gfx_SetTextXY(160 - (gfx_GetStringWidth(colors[lastPlace]) + gfx_GetStringWidth(" is last")) / 2, 90);
        gfx_PrintString(colors[lastPlace]);
        gfx_PrintString(" is last");
    }
    else if(lastPlace == -2){
        gfx_SetTextXY(160 - gfx_GetStringWidth("Why are you playing alone? :O") / 2, 90);
        gfx_PrintString("Why are you playing alone? :O");
    }
    
    gfx_PrintStringXY("Press [del] to return to the main menu", 160 - gfx_GetStringWidth("Press [del] to return to the main menu") / 2, 130);
    gfx_PrintStringXY("Press [2nd] to continue", 160 - gfx_GetStringWidth("Press [2nd] to continue") / 2, 160);
    gfx_BlitBuffer();
}

void print_wrapped_text(int x, int y, int width, char* text){
    int lineWidth = 0;
    int wordWidth = 0;
    int wordLength = 0;
    gfx_SetTextXY(x, y);
    for(int i = 0; text[i] != 0; i++){
        if(text[i] == ' ' || text[i + 1] == 0 || text[i + 1] == '#'){
            if(lineWidth + (int)gfx_GetCharWidth(' ') + wordWidth > x + width){
                lineWidth = 0;
                gfx_SetTextXY(x, gfx_GetTextY() + 9); 
            }
            for(int j = 0; j <= wordLength; j++){
                gfx_PrintChar(text[i - wordLength + j]);
            }
            lineWidth = lineWidth + gfx_GetCharWidth(' ') + wordWidth;
            wordWidth = 0;
            wordLength = 0;
        }
        else if(text[i] == '#'){
            lineWidth = 0;
            gfx_SetTextXY(x, gfx_GetTextY() + 10); 
        }
        else{
            wordWidth = wordWidth + (gfx_GetCharWidth(text[i]));
            wordLength++;
        }
    }
}

void draw_about(int page){
    gfx_SetTextXY(295, 5);
    gfx_PrintInt(page + 1, 1);
    gfx_PrintString("/3");

    if(page == 0){
        print_wrapped_text(5, 5, 310, "Rules:#The goal of the game is to move all of your pieces into the house (the row  of four fields in your color). You start by rolling the die. If all of your pieces are still at the start or only some of them and the rest at the end of the house, you may roll the die three times in a row. After rolling the die, you have to move a piece forwards by the rolled number of pieces. If you roll a 6, you have to move one of the pieces from the start to the starting field of your color. You always have to keep the starting field free. If there are no more pieces at the start, you can move any piece you want 6 fields forwards. After rolling a 6, you have to roll the die again. If one of your pieces is moved to a field which is occupied by another player, you have to move the other players figure back to the player's start. You cannot move one of your figures to a field occupied by one of your own pieces. After you completed one round around the board with a piece, you move it into the house. Other players can't enter your house, so your pieces are save there. If all of your pieces are in the house, you win the game.");
    }
    else if(page == 1){
        print_wrapped_text(5, 15, 230, "Controls:#[2nd]: Roll the die/move a piece#[\x11]/[\x10]: select the piece to move#[del]: save and return to main menu#[clear]: save and quit");
    }
    else if(page == 2){
        gfx_PrintStringXY("Credits", 160 - gfx_GetStringWidth("Credits") / 2, 65);
        gfx_PrintStringXY("Developers:", 160 - gfx_GetStringWidth("Developers:") / 2, 80);
        gfx_PrintStringXY("- einsmaxe", 160 - gfx_GetStringWidth("- einsmaxe") / 2, 90);
        gfx_PrintStringXY("- ZebraVogel94349", 160 - gfx_GetStringWidth("- ZebraVogel94349") / 2, 100);
        gfx_PrintStringXY("Special thanks to:", 160 - gfx_GetStringWidth("Special thanks to:") / 2, 120);
        gfx_PrintStringXY("2023", 160 - gfx_GetStringWidth("2023") / 2, 200);
    }
    
    gfx_BlitBuffer();
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

