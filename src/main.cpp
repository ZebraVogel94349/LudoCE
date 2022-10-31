#include <tice.h>
#include <keypadc.h>
#include <fileioc.h>
#include <graphx.h>

#include "gfx/palette_gfx.h"
#include "gfx/colors.h"
#include "const.h"
#include "ui.hpp"
#include "draw.hpp"
#include "game.hpp"

int main(){
    srand(rtc_Time());
    gfx_Begin();
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0);
    gfx_SetDrawBuffer();

    int mainMenuEntryTypes[6] = {0, 2, 1, 1, 1, 1}; // 0 = text, 1 = enabled, 2 = not enabled
    
    while(true){
        int status = 0;
        int g_status = 0;
        int playerPositions[17] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 27};
        int newGameValuesBorder[5][3] = {{2, 4}, {1, 4}, {0, 3}, {1, 4}, {1, 3}};
        int newGameValues[5] = {4, 4, 0, 4, 2}; //Player count, Player, Bots, Figure count, Bot Strength
        int newGameColors[4] = {1, 2, 3, 4}; // BLUE, RED, YELLOW, GREEN
        int toClear = 0;
        int r = 0;
        int again = 0;
        int playerTypes[4] = {2, 2, 2, 2};
        int selectedPlayer = 0;
        int oldSelection = 0;
        kb_key_t prevkey1 = kb_Data[1];
        kb_key_t prevkey7 = kb_Data[7];
        int keycount = 0;
        int selectedEntry = 2;
        int selectedNumber = 0;
        //Main Menu
        gfx_FillScreen(BACKGROUND_YELLOW);
        gfx_SwapDraw();
        gfx_FillScreen(BACKGROUND_YELLOW);
        if(status == 0){
            while(kb_Data[6] != kb_Clear){
                if(kb_Data[7] == kb_Up && (prevkey7 != kb_Up || keycount % 10 == 9)){
                    if(selectedEntry == 1){
                        selectedEntry = 5;
                    }else if(selectedEntry == 2 && mainMenuEntryTypes[1] == 2){
                        selectedEntry = 5;
                    }
                    else{
                        selectedEntry--;
                    }
                }
                if(kb_Data[7] == kb_Down && (prevkey7 != kb_Down || keycount % 10 == 9)){
                    if(selectedEntry == 5){
                        if(mainMenuEntryTypes[1] == 2){
                            selectedEntry = 2;
                        }else{
                            selectedEntry = 1;
                        }
                    }
                    else{
                        selectedEntry++;
                    }
                }
                if(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd){
                    if(selectedEntry == 1){ // load game
                        // code for loading game
                    }
                    else if(selectedEntry == 2){ //start new game
                        status = 1;
                        break;
                    }
                    else if(selectedEntry == 4){ //open credits
                        status = 2;
                        break;
                    }
                    else if(selectedEntry == 5){ //exit
                        status = 4;
                        break;
                    }
                }
                draw_main_menu(selectedEntry, mainMenuEntryTypes);
                
                if(kb_Data[7] == prevkey7)
                {
                    keycount = keycount + 1;
                }
                else
                {
                    keycount = 0;
                }  
                prevkey1 = kb_Data[1];
                prevkey7 = kb_Data[7];
                kb_Scan();
            }
            prevkey1 = kb_Data[1];
        }
        if(status == 0){
            status = 4;
        }

        if(status == 1){
            while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && status == 1){
                if(kb_Data[7] == kb_Up && (prevkey7 != kb_Up || keycount % 10 == 9)){
                    if(selectedEntry == 1){
                        selectedEntry = 7;
                    }
                    else{
                        selectedEntry--;
                    }
                }
                if(kb_Data[7] == kb_Down && (prevkey7 != kb_Down || keycount % 10 == 9)){
                    if(selectedEntry == 7){
                        selectedEntry = 1;
                    }
                    else{
                        selectedEntry++;
                    }
                }
                if(kb_Data[7] == kb_Left && (prevkey7 != kb_Left || keycount % 10 == 9) && selectedEntry < 6){
                    selectedNumber = newGameValues[selectedEntry - 1];
                    if(selectedNumber == newGameValuesBorder[selectedEntry - 1][0]){
                        selectedNumber = newGameValues[selectedEntry - 1];
                    }
                    else{
                        selectedNumber--;
                    }
                    newGameValues[selectedEntry - 1] = selectedNumber;

                    // Fit other values
                    if(selectedEntry == 1){ // player count
                        newGameValuesBorder[1][1] = newGameValues[0]; // new max for players
                        newGameValuesBorder[2][1] = newGameValues[0] - 1; // new max for bots
                        if(newGameValues[2] > 0){
                            newGameValues[2] = newGameValues[0] - newGameValues[1]; // new value for bots
                        }else{
                            newGameValues[1] = newGameValues[0] - newGameValues[2]; // new value for players
                        }
                    }
                    else if(selectedEntry == 2){ // players
                        newGameValues[2] = newGameValues[0] - newGameValues[1]; // new value for bots
                    }
                    else if(selectedEntry == 3){ // bots
                        newGameValues[1] = newGameValues[0] - newGameValues[2]; // new value for players
                    }
                }
                if(kb_Data[7] == kb_Right && (prevkey7 != kb_Right || keycount % 10 == 9) && selectedEntry < 6){
                    selectedNumber = newGameValues[selectedEntry - 1];
                    if(selectedNumber == newGameValuesBorder[selectedEntry - 1][1]){
                        selectedNumber = newGameValues[selectedEntry - 1];
                    }
                    else{
                        selectedNumber++;
                    }
                    newGameValues[selectedEntry - 1] = selectedNumber;

                    // Fit other values
                    if(selectedEntry == 1){ // player count
                        newGameValuesBorder[1][1] = newGameValues[0]; // new max for players
                        newGameValuesBorder[2][1] = newGameValues[0] - 1; // new max for bots
                        newGameValues[1] = newGameValues[0] - newGameValues[2]; // new value for players
                    }
                    else if(selectedEntry == 2){ // players
                        newGameValues[2] = newGameValues[0] - newGameValues[1]; // new value for bots
                    }
                    else if(selectedEntry == 3){ // bots
                        newGameValues[1] = newGameValues[0] - newGameValues[2]; // new value for players
                    }
                }
                if(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd){
                    if(selectedEntry == 5){ // color selection
                        // COLOR SELECTIOn MENU HERE   
                    }else if(selectedEntry == 7){ // start new game
                        // apply values                                                                                            !!!temporary until color selection is implemented!!!
                        for(int i = 0; i < newGameValues[1]; i++){ // assign players
                            playerTypes[i] = 0;
                        }
                        for(int i = newGameValues[1]; i < newGameValues[0]; i++){ // assign bots
                            playerTypes[i] = 1;
                        }
                        //apply bot strength here//

                        g_status = 1;
                    }
                    break;
                }
                draw_new_game_menu(selectedEntry, newGameValues);

                if(kb_Data[7] == prevkey7)
                {
                    keycount = keycount + 1;
                }
                else
                {
                    keycount = 0;
                }  
                prevkey1 = kb_Data[1];
                prevkey7 = kb_Data[7];
                kb_Scan();
            }
            status = 0;
            prevkey1 = kb_Data[1];
        }

        if(g_status == 1){
            gfx_FillScreen(BACKGROUND_YELLOW);
            draw_board();
            draw_player(playerPositions, 0, BOARD_DATA[0]);
        
            gfx_SwapDraw();

            gfx_FillScreen(BACKGROUND_YELLOW);
            draw_board();
            draw_player(playerPositions, 0, BOARD_DATA[0]);
            while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions)){
                for(int i = 2; i < 2 + BOARD_DATA[4] && kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions); i++){
                    again = 1;
                    if(playerTypes[i - 2] == 0){//if it's a real player's turn
                        r = 0;
                        draw_everything(playerPositions, toClear, r);
                        for(int k = 0; k < again && kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions); k++){
                            while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del){//wait for 2nd to roll the die
                                if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//roll the die
                                    r = rand() % 6 + 1;
                                    break;
                                }
                                prevkey1 = kb_Data[1];
                                prevkey7 = kb_Data[7];
                                kb_Scan();
                            }
                            draw_everything(playerPositions, toClear, r);
                            prevkey1 = kb_Data[1];
                            prevkey7 = kb_Data[7];
                            kb_Scan();
                            for(int j = 0; j < BOARD_DATA[2]; j++){ 
                                if(is_player_movable(playerPositions, i, j, r)){
                                    selectedPlayer = j;
                                    break;
                                }else{
                                    selectedPlayer = -1;
                                }
                            }
                            if(selectedPlayer != -1){
                                while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del){//wait for 2nd to move the player
                                    // draw selections
                                    draw_everything(playerPositions, toClear, r);
                                    draw_potential_field(move_n_fields(i, playerPositions[(i - 2) * BOARD_DATA[2] + selectedPlayer], r), move_n_fields(i, playerPositions[(i - 2) * BOARD_DATA[2] + oldSelection], r));
                                    draw_player_selection(playerPositions, (i - 2) * BOARD_DATA[2] + selectedPlayer, (i - 2) * BOARD_DATA[2] + oldSelection);
                                    
                                    if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//move the player
                                        *playerPositions = *move_player(playerPositions, i, selectedPlayer, r);
                                        toClear = playerPositions[BOARD_DATA[0]];
                                        draw_field_pos(playerPositions[(i - 2) * BOARD_DATA[2] + selectedPlayer]);
                                        gfx_SwapDraw();
                                        draw_field_pos(playerPositions[(i - 2) * BOARD_DATA[2] + selectedPlayer]);
                                        draw_everything(playerPositions, toClear, r);
                                        break;
                                    }
                                    
                                    if(kb_Data[7] == kb_Left && kb_Data[7] != prevkey7){
                                        oldSelection = selectedPlayer;
                                        for(int j = 0; j < BOARD_DATA[2]; j++){ 
                                            if(selectedPlayer > 0){
                                                selectedPlayer--;
                                            }
                                            else{
                                                selectedPlayer = BOARD_DATA[2] - 1;
                                            }
                                            if(is_player_movable(playerPositions, i, selectedPlayer, r)){
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if(kb_Data[7] == kb_Right && kb_Data[7] != prevkey7){
                                        oldSelection = selectedPlayer;
                                        for(int j = 0; j < BOARD_DATA[2]; j++){ 
                                            if(selectedPlayer < BOARD_DATA[2] - 1){
                                                selectedPlayer++;
                                            }
                                            else{
                                                selectedPlayer = 0;
                                            }
                                            if(is_player_movable(playerPositions, i, selectedPlayer, r)){
                                                break;
                                            }
                                        }
                                    }
                                    prevkey1 = kb_Data[1];
                                    prevkey7 = kb_Data[7];
                                    kb_Scan();
                                }
                                prevkey1 = kb_Data[1];
                                prevkey7 = kb_Data[7];
                                kb_Scan();
                            }
                            if(check_for_order(playerPositions, i) && again < 3){
                                again++;
                            }   
                        }
                        msleep(500);
                    }
                    else if(playerTypes[i - 2] == 1){
                        for(int k = 0; k < again && kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions); k++){
                            r = rand() % 6 + 1;
                            *playerPositions = *move_enemy(playerPositions, i, r);
                            toClear = playerPositions[BOARD_DATA[0]];
                            draw_everything(playerPositions, toClear, r);
                            
                            msleep(500);

                            prevkey1 = kb_Data[1];
                            prevkey7 = kb_Data[7];
                            kb_Scan();

                            if(check_for_order(playerPositions, i) && again < 3){
                                again++;
                            }  
                        }
                    }
                    if(r == 6){i--;}
                }
            }
            status = 0;
        }
        if(status == 2){
            gfx_FillScreen(BACKGROUND_YELLOW);
            gfx_SwapDraw();
            gfx_FillScreen(BACKGROUND_YELLOW);
            draw_credits();
            while(kb_Data[6] != kb_Clear && !(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd) && kb_Data[1] != kb_Del && status == 2){
                prevkey1 = kb_Data[1];
                kb_Scan();
            }
            status = 0;
            prevkey1 = kb_Data[1];
        }
        if(status == 4){
            break;
        }
    }

    
    gfx_End();
}