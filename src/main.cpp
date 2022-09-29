#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>
#include <fileioc.h>
#include <graphx.h>

#include "gfx/palette_gfx.h"
#include "gfx/colors.h"
#include "const.h"


void draw_field(int x, int y, int r, int color){
    gfx_SetColor(BLACK);
    gfx_FillCircle_NoClip(x + 10, y + 10, r);
    gfx_SetColor(color);
    gfx_FillCircle_NoClip(x + 10, y + 10, r - 1);
}

void connect_fields(int x0, int y0, int x1, int y1){
    gfx_SetColor(BLACK);
    gfx_Line(x0 + 10, y0 + 10, x1 + 10, y1 + 10);
}

void draw_board(){
    for(int i = 0; i < BOARD_DATA.end_of_board; i++){
        connect_fields(BOARD[i][0], BOARD[i][1], BOARD[i + 1][0], BOARD[i + 1][1]);
    }
    connect_fields(BOARD[BOARD_DATA.end_of_board][0], BOARD[BOARD_DATA.end_of_board][1], BOARD[0][0], BOARD[0][1]);
    for(int i = 0; i < 72; i++){
        draw_field(BOARD[i][0], BOARD[i][1], 8, BOARD[i][2]);
    }
}

void redraw_field(int position){
    draw_field(BOARD[position][0], BOARD[position][1], 8, BOARD[position][2]);
}

void draw_player(int playerPositions[], int start, int end){
    for(int i = start; i < end; i++){
        if(i >= BOARD_DATA.GREEN.playerNumberStart){
            draw_field(BOARD[playerPositions[i]][0], BOARD[playerPositions[i]][1], 5, GREEN);
        }
        else if(i >= BOARD_DATA.YELLOW.playerNumberStart){
            draw_field(BOARD[playerPositions[i]][0], BOARD[playerPositions[i]][1], 5, YELLOW);
        }
        else if(i >= BOARD_DATA.RED.playerNumberStart){
            draw_field(BOARD[playerPositions[i]][0], BOARD[playerPositions[i]][1], 5, RED);
        }
        else{
            draw_field(BOARD[playerPositions[i]][0], BOARD[playerPositions[i]][1], 5, BLUE);
        }
    }
}

int occupied_by(int position, int playerPositions[]){
    for(int i = 0; i < BOARD_DATA.player_count; i++){
        if(playerPositions[i] == position){
            return i;
        }
    }
    return -1;
}

int move_n_fields(int piece_color, int position, int n){
    int h_offset, h_start, startPoint;

    switch (piece_color){
        case BLUE:
            startPoint = BOARD_DATA.BLUE.startPoint;
            h_offset = BOARD_DATA.BLUE.h_offset;
            h_start = BOARD_DATA.BLUE.h_start;
            break;
        case RED:
            startPoint = BOARD_DATA.RED.startPoint;
            h_offset = BOARD_DATA.RED.h_offset;
            h_start = BOARD_DATA.RED.h_start;
            break;
        case YELLOW:
            startPoint = BOARD_DATA.YELLOW.startPoint;
            h_offset = BOARD_DATA.YELLOW.h_offset;
            h_start = BOARD_DATA.YELLOW.h_start;
            break;
        case GREEN:
            startPoint = BOARD_DATA.GREEN.startPoint;
            h_offset = BOARD_DATA.GREEN.h_offset;
            h_start = BOARD_DATA.GREEN.h_start;
            break;
    }
    if(position >= 56 && n == 6){//move out of home
        return startPoint;
    }
    else if(position <= h_offset && position + n > h_offset && position + n <= h_offset + BOARD_DATA.h_size){//move into house
        return h_start + (position + n - (h_offset + 1));
    }
    else if(position <= h_offset && position + n > h_offset){//dont move if you cant move any further
        return position;
    }

    else if((position >= h_start && position + n < h_start + BOARD_DATA.h_size)){//move inside house
        return position + n;
    }
    else if(position + n <= BOARD_DATA.end_of_board){//move normally
        return position + n;
    }
    else if(position <= BOARD_DATA.end_of_board){//go from end of board to 0
        return position + n - (BOARD_DATA.end_of_board + 1);
    }
    else{
        return position;
    }
}

int get_color(int playerNumber){
    if(playerNumber >= BOARD_DATA.GREEN.playerNumberStart){
        return GREEN;
    }
    else if(playerNumber >= BOARD_DATA.YELLOW.playerNumberStart){
        return YELLOW;
    }
    else if(playerNumber >= BOARD_DATA.RED.playerNumberStart){
        return RED;
    }
    else{
        return BLUE;
    }
}

int *throw_out(int playerPositions[], int piece_color, int player, int old_position, int n){
    int new_position = move_n_fields(piece_color, old_position, n);
    int occupyingPlayer = occupied_by(new_position, playerPositions);
    
    playerPositions[occupyingPlayer] = BOARD_DATA.BLUE.hm_pos + occupyingPlayer;
    playerPositions[player] = new_position;
    return playerPositions;
}

int check_for_order(int playerPositions[], int piece_color){
    int h_start, playerNumberStart;
    bool houseFieldIsOccupied = true;
    int fields = 0;
    if(piece_color == BLUE){
        h_start = BOARD_DATA.BLUE.h_start;
        playerNumberStart = BOARD_DATA.BLUE.playerNumberStart;
    }
    else if(piece_color == RED){
        h_start = BOARD_DATA.RED.h_start;
        playerNumberStart = BOARD_DATA.RED.playerNumberStart;
    }
    else if(piece_color == YELLOW){
        h_start = BOARD_DATA.YELLOW.h_start;
        playerNumberStart = BOARD_DATA.YELLOW.playerNumberStart;
    }
    else{
        h_start = BOARD_DATA.GREEN.h_start;
        playerNumberStart = BOARD_DATA.GREEN.playerNumberStart;
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        if(playerPositions[i] < h_start){//if player on the field
            return false;
        }
        else if(playerPositions[i] >= BOARD_DATA.BLUE.hm_pos){//one more player in home
            fields++;
        }
    }
    if(fields == 4){//if all players in home
        return true;
    }
    else{
        fields = 0;//otherwise reset fields
    }

    for(int j = 1; j < BOARD_DATA.h_size; j++){
        for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
            if(playerPositions[i] == h_start + BOARD_DATA.h_size - j){
                houseFieldIsOccupied = true;
                fields++;
                break;
            }
            else{
                houseFieldIsOccupied = false;
            }
        }
        if(!houseFieldIsOccupied && fields == 0){//no player on the last house field
            return false;
        }
        else if(houseFieldIsOccupied && fields != j){//no order
            return false;
        }
    }
    return true;
}

void draw(int playerPositions[], int toClear, int color, int number){
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    if(occupied_by(toClear, playerPositions) == -1){
        redraw_field(toClear);
    }
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    if(number != 0){
        gfx_SetTextFGColor(color);
        gfx_SetTextXY(6,6);
        gfx_PrintInt(number, 1);
    }
    
    
    gfx_SwapDraw();

    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    if(occupied_by(toClear, playerPositions) == -1){
        redraw_field(toClear);
    }
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    if(number != 0){
        gfx_SetTextFGColor(color);
        gfx_SetTextXY(6,6);
        gfx_PrintInt(number, 1);
    }
}

void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection){
    redraw_field(playerPositions[oldSelection]);
    draw_field(BOARD[playerPositions[selectedPlayer]][0], BOARD[playerPositions[selectedPlayer]][1], 7, BLACK);
}

int *move_enemy(int playerPositions[], int piece_color, int n){
    int hm_pos, playerNumberStart, occupyingPlayer, startPoint, movable;
    bool allOut = true;
    movable = -1;
    if(piece_color == BLUE){
        hm_pos = BOARD_DATA.BLUE.hm_pos;
        playerNumberStart = BOARD_DATA.BLUE.playerNumberStart;
        startPoint = BOARD_DATA.BLUE.startPoint;
    }
    else if(piece_color == RED){
        hm_pos = BOARD_DATA.RED.hm_pos;
        playerNumberStart = BOARD_DATA.RED.playerNumberStart;
        startPoint = BOARD_DATA.RED.startPoint;
    }
    else if(piece_color == YELLOW){
        hm_pos = BOARD_DATA.YELLOW.hm_pos;
        playerNumberStart = BOARD_DATA.YELLOW.playerNumberStart;
        startPoint = BOARD_DATA.YELLOW.startPoint;
    }
    else{
        hm_pos = BOARD_DATA.GREEN.hm_pos;
        playerNumberStart = BOARD_DATA.GREEN.playerNumberStart;
        startPoint = BOARD_DATA.GREEN.startPoint;
    }

    occupyingPlayer = occupied_by(startPoint, playerPositions);
    if(occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color){
        for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
            if(n == 6 && playerPositions[i] >= hm_pos){
                playerPositions[16] = playerPositions[i];//store the old position of the player in playerPositions[16]
                if(occupyingPlayer != -1){
                    playerPositions = throw_out(playerPositions, piece_color, i, playerPositions[i], n);//move player out of home if you have to + throw out player
                    return playerPositions;
                }else{
                    playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player out of home if you have to 
                    return playerPositions;
                }
            }
        }
    }
    
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        if(playerPositions[i] >= hm_pos){
            allOut = false;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] == startPoint && (occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color) && !allOut){
            playerPositions[16] = playerPositions[i];
            playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player from start point if you have to
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] <= BOARD_DATA.end_of_board && move_n_fields(piece_color, playerPositions[i], n) > BOARD_DATA.end_of_board && occupyingPlayer == -1){
            playerPositions[16] = playerPositions[i];
            playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//priorize entering the house
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer != -1 && get_color(occupyingPlayer) != piece_color && rand() % 10 != 0){
            playerPositions[16] = playerPositions[i];
            playerPositions = throw_out(playerPositions, piece_color, i, playerPositions[i], n);//throw out player
            return playerPositions;
        }
    }
    
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer == -1 && move_n_fields(piece_color, playerPositions[i], n) != playerPositions[i]){
            movable = i;
            if(rand() % 4 != 0){
                playerPositions[16] = playerPositions[i];
                playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player to empty field
                return playerPositions;
            }   
        }
    }
    if(movable != -1){//move a movable player, if not done before
        playerPositions[16] = playerPositions[movable];
        playerPositions[movable] = move_n_fields(piece_color, playerPositions[movable], n);//move player to empty field
    }
    return playerPositions;
}

int main(){
    int playerPositions[17] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 27};
    int toClear = 0;
    int r = 1;
    int playerTypes[4] = {1, 1, 1, 0};
    int selectedPlayer = 0;
    int oldSelection = 0;
    kb_key_t prevkey1 = kb_Data[1];
    kb_key_t prevkey7 = kb_Data[7];
    gfx_Begin();
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0);
    gfx_SetDrawBuffer();

    srand(rtc_Time());

    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    gfx_SwapDraw();


    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();
    draw_player(playerPositions, 0, BOARD_DATA.player_count);

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        for(int i = 2; i < 6 && kb_Data[6] != kb_Clear; i++){
            if(playerTypes[i - 2] == 0){//if it's a real player's turn
                for(int again = 0; again < 3 && kb_Data[6] != kb_Clear; again++){
                    while(kb_Data[6] != kb_Clear){//wait for 2nd to roll the die
                        draw(playerPositions, toClear, i, 0);
                        if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//roll the die
                            r = rand() % 6 + 1;
                            break;
                        }
                        prevkey1 = kb_Data[1];
                        prevkey7 = kb_Data[7];
                        kb_Scan();
                    }
                    prevkey1 = kb_Data[1];
                    prevkey7 = kb_Data[7];
                    kb_Scan();
                    selectedPlayer = 0;
                    while(kb_Data[6] != kb_Clear){//wait for 2nd to move the player
                        draw(playerPositions, toClear, i, r);
                        draw_player_selection(playerPositions, (i - 2) * BOARD_DATA.h_size + selectedPlayer, (i - 2) * BOARD_DATA.h_size + oldSelection);
                        if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//move the player
                        //REPLACE THIS WITH NEW MOVEMENT CODE
                            *playerPositions = *move_enemy(playerPositions, i, r);
                            toClear = playerPositions[16];
                            draw(playerPositions, toClear, i, r);
                            break;
                        }
                        if(kb_Data[7] == kb_Left && kb_Data[7] != prevkey7){
                            if(selectedPlayer > 0){
                                oldSelection = selectedPlayer;
                                selectedPlayer--;
                            }
                            else{
                                oldSelection = selectedPlayer;
                                selectedPlayer = BOARD_DATA.h_size - 1;
                            }    
                        }
                        
                        if(kb_Data[7] == kb_Right && kb_Data[7] != prevkey7){
                            if(selectedPlayer < BOARD_DATA.h_size - 1){
                                oldSelection = selectedPlayer;
                                selectedPlayer++;
                            }
                            else{
                                oldSelection = selectedPlayer;
                                selectedPlayer = 0;
                            } 
                        }
                        prevkey1 = kb_Data[1];
                        prevkey7 = kb_Data[7];
                        kb_Scan();
                    }            
                    if(!check_for_order(playerPositions, i)){
                        break;
                    }
                }
                msleep(1000);
                }

            else{
                for(int again = 0; again < 3 && kb_Data[6] != kb_Clear; again++){
                r = rand() % 6 + 1;
                *playerPositions = *move_enemy(playerPositions, i, r);
                toClear = playerPositions[16];
                draw(playerPositions, toClear, i, r);
                
                msleep(1000);

                prevkey1 = kb_Data[1];
                prevkey7 = kb_Data[7];
                kb_Scan();

                if(!check_for_order(playerPositions, i)){
                    break;
                }

                
            }
            }
            if(r == 6){i--;}
        }
    }
    gfx_End();
    
}