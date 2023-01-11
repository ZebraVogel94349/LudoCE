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
    int savearr[26] = {-1};
    bool loadEnabled = false;
    ti_var_t sv;

    srand(rtc_Time());
    gfx_Begin();
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0);
    gfx_SetDrawBuffer();
    while(true){
        sv = ti_Open("LUDOSV","r");
	    if(sv != 0){
            ti_Read(savearr,78,1,sv);
            ti_Close(sv);
            loadEnabled = true;
        }
        if(savearr[0] != -1 && savearr[0] != VERSION){//Delete the saved game if the version differs
            ti_Delete("LUDOSV");
            for(int i = 0; i < 26; i++){
                savearr[i] = 0;
            }
            loadEnabled = false;
        }

        int status = 0;
        int playerPositions[17] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 27};
        int gameSettingsBorder[5][2] = {{1, 4}, {0, 4}, {0, 4}, {1, 4}, {0, 2}};
        int gameSettings[5] = {4, 4, 0, 4, 1}; //Player count, Player, Bots, Figure count, Bot Strength
        int r = 0;
        int again = 0;
        int playerTypes[4] = {2, 2, 2, 2};
        int selectedPlayer = 0;
        int oldSelection = 0;
        kb_key_t prevkey1 = kb_Data[1];
        kb_key_t prevkey7 = kb_Data[7];
        int keycount = 0;
        int selectedEntry = 1;
        int currentPlayerSave = savearr[4];
        int againSave = savearr[5];
        
        gfx_FillScreen(BACKGROUND_YELLOW);
        gfx_SwapDraw();
        gfx_FillScreen(BACKGROUND_YELLOW);
        if(status == 0){//Main Menu
            while(kb_Data[6] != kb_Clear){
                selectedEntry = menu_up_down(keycount, selectedEntry, 4, prevkey7);
                if(selectedEntry == 0 && !loadEnabled){//Skip disabled entry
                    selectedEntry = menu_up_down(keycount, selectedEntry, 4, prevkey7);
                }
                if(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd){
                    if(selectedEntry == 0){//Load Game
                        gameSettings[0] = savearr[1];
                        gameSettings[3] = savearr[2];
                        gameSettings[4] = savearr[3];
                        for(int i = 0; i < BOARD_DATA[2]; i++){
                            playerTypes[i] = savearr[6 + i];
                        }
                        for(int i = 0; i < BOARD_DATA[0]; i++){
                            playerPositions[i] = savearr[6 + BOARD_DATA[2] + i];
                        }
                        status = 6;
                        break;
                    }
                    status = selectedEntry;
                    break;
                }
                draw_main_menu(selectedEntry, loadEnabled);
                
                if(kb_Data[7] == prevkey7){
                    keycount = keycount + 1;
                }
                else{
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

        if(status == 1){//New game menu
            currentPlayerSave = 0;
            againSave = 0;
            while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && status == 1){
                selectedEntry = menu_up_down(keycount, selectedEntry, 6, prevkey7);
                if(kb_Data[7] == kb_Left && (prevkey7 != kb_Left || keycount % 10 == 9) && selectedEntry < 5){
                    if(gameSettings[selectedEntry] != gameSettingsBorder[selectedEntry][0]){
                        gameSettings[selectedEntry]--;
                    }
                    if(selectedEntry == 1 && gameSettings[1] + gameSettings[2] == 0){ //stay inside the player limit
                        gameSettings[2]++;
                    }
                    else if(selectedEntry == 2 && gameSettings[1] + gameSettings[2] == 0){ //stay inside the player limit
                        gameSettings[1]++;
                    }
                }
                if(kb_Data[7] == kb_Right && (prevkey7 != kb_Right || keycount % 10 == 9) && selectedEntry < 5){
                    if(gameSettings[selectedEntry] != gameSettingsBorder[selectedEntry][1]){
                        gameSettings[selectedEntry]++;
                    }
                    if(selectedEntry == 1 && gameSettings[1] + gameSettings[2] > gameSettingsBorder[0][1]){ //stay inside the player limit
                        gameSettings[2]--;
                    }
                    else if(selectedEntry == 2 && gameSettings[1] + gameSettings[2] > gameSettingsBorder[0][1]){ //stay inside the player limit
                        gameSettings[1]--;
                    }
                }
                if(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd){
                    if(selectedEntry == 5){ // color selection
                        // COLOR SELECTION MENU HERE   
                        status = 5;
                    }else if(selectedEntry == 6){ // start new game
                        for(int i = 0; i < gameSettings[1]; i++){ // assign players
                            playerTypes[i] = 0;
                        }
                        for(int i = gameSettings[1]; i < gameSettings[1] + gameSettings[2]; i++){ // assign bots
                            playerTypes[i] = 1;
                        }
                        for(int i = (gameSettings[1] + gameSettings[2]) * 4; i < BOARD_DATA[0]; i++){//Set position of all disabled colors to -1
                            playerPositions[i] = -1;
                        }
                        for(int i = 0; i < (gameSettings[1] + gameSettings[2]) * 4; i++){//Set position of all disabled figures to -1
                            if(i % BOARD_DATA[2] >= gameSettings[3]){
                                playerPositions[i] = -1;
                            }         
                        }
                        status = 6;
                    }
                }
                draw_new_game_menu(selectedEntry, gameSettings);

                if(kb_Data[7] == prevkey7){
                    keycount = keycount + 1;
                }
                else{
                    keycount = 0;
                }  
                prevkey1 = kb_Data[1];
                prevkey7 = kb_Data[7];
                kb_Scan();
            }
            prevkey1 = kb_Data[1];
        }

        if(status == 6){
            gfx_FillScreen(BACKGROUND_YELLOW);
            draw_board();
            draw_player(playerPositions, 0, BOARD_DATA[0]);
        
            gfx_SwapDraw();

            gfx_FillScreen(BACKGROUND_YELLOW);
            draw_board();
            draw_player(playerPositions, 0, BOARD_DATA[0]);
            while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del){
                for(int i = 2; i < 2 + BOARD_DATA[4] && kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions, gameSettings[3]); i++){
                    if(currentPlayerSave != 0){
                        i = currentPlayerSave;
                        currentPlayerSave = 0;
                    }
                    again = 1;
                    if(againSave != 0){
                        again = againSave;
                        againSave = 0;
                    }
                    if(playerTypes[i - 2] == 0){//if it's a real player's turn
                        r = 0;
                        draw_everything(playerTypes, gameSettings, playerPositions, playerPositions[BOARD_DATA[0]], r, i);
                        for(int k = again - 1; k < again && kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions, gameSettings[3]); k++){
                            while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1)){//wait for 2nd to roll the die
                                prevkey1 = kb_Data[1];
                                kb_Scan();
                            }
                            if(kb_Data[6] == kb_Clear){
                                break;
                            }
                            r = rand() % 6 + 1;
                            draw_everything(playerTypes, gameSettings, playerPositions, playerPositions[BOARD_DATA[0]], r, i);
                            prevkey1 = kb_Data[1];
                            prevkey7 = kb_Data[7];
                            kb_Scan();
                            for(int j = 0; j < gameSettings[3]; j++){//select the first movable player
                                if(is_player_movable(playerPositions, i, j, r, gameSettings[3])){
                                    selectedPlayer = j;
                                    break;
                                }else{
                                    selectedPlayer = -1;
                                }
                            }
                            if(selectedPlayer != -1){
                                while(kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del){//wait for 2nd to move the player
                                    // draw selections
                                    draw_everything(playerTypes, gameSettings, playerPositions, playerPositions[BOARD_DATA[0]], r, i);
                                    draw_potential_field(move_n_fields(i, playerPositions[(i - 2) * BOARD_DATA[2] + selectedPlayer], r), move_n_fields(i, playerPositions[(i - 2) * BOARD_DATA[2] + oldSelection], r));
                                    draw_player_selection(playerPositions, (i - 2) * BOARD_DATA[2] + selectedPlayer, (i - 2) * BOARD_DATA[2] + oldSelection);
                                    
                                    if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//move the player
                                        *playerPositions = *move_player(playerPositions, i, selectedPlayer, r);
                                        draw_field_pos(playerPositions[(i - 2) * BOARD_DATA[2] + selectedPlayer]);
                                        draw_everything(playerTypes, gameSettings, playerPositions, playerPositions[BOARD_DATA[0]], r, i);
                                        draw_field_pos(playerPositions[(i - 2) * BOARD_DATA[2] + selectedPlayer]);
                                        break;
                                    }
                                    
                                    if(kb_Data[7] == kb_Left && kb_Data[7] != prevkey7){
                                        oldSelection = selectedPlayer;
                                        for(int j = 0; j < gameSettings[3]; j++){ 
                                            if(selectedPlayer > 0){
                                                selectedPlayer--;
                                            }
                                            else{
                                                selectedPlayer = gameSettings[3] - 1;
                                            }
                                            if(is_player_movable(playerPositions, i, selectedPlayer, r, gameSettings[3])){
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if(kb_Data[7] == kb_Right && kb_Data[7] != prevkey7){
                                        oldSelection = selectedPlayer;
                                        for(int j = 0; j < gameSettings[3]; j++){ 
                                            if(selectedPlayer < gameSettings[3] - 1){
                                                selectedPlayer++;
                                            }
                                            else{
                                                selectedPlayer = 0;
                                            }
                                            if(is_player_movable(playerPositions, i, selectedPlayer, r, gameSettings[3])){
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
                            if(check_for_order(playerPositions, i, gameSettings[3]) && again < 3){
                                again++;
                            }
                            savearr[4] = i;
                            if(k + 1 == again){//increase the saved current player by 1 if quit at the end of the current's player move
                                savearr[4]++;
                            }
                            savearr[5] = again;
                        }
                    }
                    else if(playerTypes[i - 2] == 1){
                        for(int k = again - 1; k < again && kb_Data[6] != kb_Clear && kb_Data[1] != kb_Del && !check_for_win(playerPositions, gameSettings[3]); k++){
                            r = rand() % 6 + 1;
                            *playerPositions = *move_enemy(playerPositions, i, r, gameSettings[4], gameSettings[3]);
                            draw_everything(playerTypes, gameSettings, playerPositions, playerPositions[BOARD_DATA[0]], r, i);
                            
                            msleep(500);
                            
                            kb_Scan();

                            if(check_for_order(playerPositions, i, gameSettings[3]) && again < 3){
                                again++;
                            } 
                            savearr[4] = i;
                            if(k + 1 == again){//increase the saved current player by 1 if quit at the end of the current's player move
                                savearr[4]++;
                            }
                            savearr[5] = again;
                        }
                    }
                    if(r == 6){i--;}
                }
                if(int winner = check_for_win(playerPositions, gameSettings[3])){
                    draw_win_screen(winner);
                    while(kb_Data[6] != kb_Clear && !(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd) && kb_Data[1] != kb_Del){
                        prevkey1 = kb_Data[1];
                        kb_Scan();
                    }
                    break;
                }
            }
            status = 0;

            
            savearr[0] = VERSION;
            savearr[1] = gameSettings[0];
            savearr[2] = gameSettings[3];
            savearr[3] = gameSettings[4];
            for(int i = 0; i < BOARD_DATA[2]; i++){
                savearr[6 + i] = playerTypes[i];
            }
            for(int i = 0; i < BOARD_DATA[0]; i++){
                savearr[6 + BOARD_DATA[2] + i] = playerPositions[i];
            }
	        sv = ti_Open("LUDOSV","w");
            ti_Write(savearr,78,1,sv);
	        ti_SetArchiveStatus(true, sv);
            ti_Close(sv);
        }
        if(status == 3){
            gfx_FillScreen(BACKGROUND_YELLOW);
            draw_credits();
            while(kb_Data[6] != kb_Clear && !(kb_Data[1] == kb_2nd && prevkey1 != kb_2nd) && kb_Data[1] != kb_Del){
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