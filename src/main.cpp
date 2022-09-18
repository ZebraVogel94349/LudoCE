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
    if(position == 0){
        draw_field(BOARD[0][0], BOARD[0][1], 8, BOARD[0][2]);
    }
    else{
        draw_field(BOARD[position][0], BOARD[position][1], 8, BOARD[position][2]);
    }
}

void draw_player(int color, int position){
    draw_field(BOARD[position][0], BOARD[position][1], 5, color);
}

int is_occupied(int position, int playerPositions[]){
    for(int i = 0; i < BOARD_DATA.player_count; i++){
        if(playerPositions[i] == position){
            return true;
        }
    }
    return false;
}

int move_n_fields(int piece_color, int player, int position, int n){
    int h_size, h_offset, h_start, hm_pos, startPoint;

    switch (piece_color){
        case BLUE:
            hm_pos = BOARD_DATA.BLUE.hm_pos + player;
            startPoint = BOARD_DATA.BLUE.startPoint;
            h_size = BOARD_DATA.BLUE.h_size;
            h_offset = BOARD_DATA.BLUE.h_offset;
            h_start = BOARD_DATA.BLUE.h_start;
            break;
        case RED:
            hm_pos = BOARD_DATA.RED.hm_pos + player;
            startPoint = BOARD_DATA.RED.startPoint;
            h_size = BOARD_DATA.RED.h_size;
            h_offset = BOARD_DATA.RED.h_offset;
            h_start = BOARD_DATA.RED.h_start;
            break;
        case YELLOW:
            hm_pos = BOARD_DATA.YELLOW.hm_pos + player;
            startPoint = BOARD_DATA.YELLOW.startPoint;
            h_size = BOARD_DATA.YELLOW.h_size;
            h_offset = BOARD_DATA.YELLOW.h_offset;
            h_start = BOARD_DATA.YELLOW.h_start;
            break;
        case GREEN:
            hm_pos = BOARD_DATA.GREEN.hm_pos + player;
            startPoint = BOARD_DATA.GREEN.startPoint;
            h_size = BOARD_DATA.GREEN.h_size;
            h_offset = BOARD_DATA.GREEN.h_offset;
            h_start = BOARD_DATA.GREEN.h_start;
            break;
    }
    if(position == hm_pos && n == 6){//move out of home
        return startPoint;
    }
    else if(position <= h_offset && position + n > h_offset && position + n <= h_offset + h_size){//move into house
        return h_start + (position + n - (h_offset + 1));
    }
    else if(position <= h_offset && position + n > h_offset){//dont move if you cant move any further
        return position;
    }

    else if((position >= h_start && position + n < h_start + h_size)){//move inside house
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

    /*// throw out or scip player 
    for(int i = 0; i < BOARD_DATA.player_count; i++){
        if(PLAYER[playerNumber] == PLAYER[i] && (i < playerNumberStart || i > playerNumberStart + 3)){
            PLAYER[i] = BOARD_DATA.BLUE.hm_pos + i;
            
            // redraw player in home
            draw_player(i);
            break;
        }else if(PLAYER[playerNumber] == PLAYER[i] && i >= playerNumberStart && i <= playerNumberStart + 3 && i != playerNumberStart + player){
            PLAYER[playerNumber] = position; // dont move
            break;
        }
    }*/
}

int main(){
    int playerPositions[16] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71};
    int toClear = 0;
    gfx_Begin();
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0);
    gfx_SetDrawBuffer();

    srand(rtc_Time());

    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();

    for(int i = 0; i < BOARD_DATA.player_count; i++){//Draw all players
        if(i >= BOARD_DATA.GREEN.playerNumberStart){
            draw_player(GREEN, playerPositions[i]);
        }
        else if(i >= BOARD_DATA.YELLOW.playerNumberStart){
            draw_player(YELLOW, playerPositions[i]);
        }
        else if(i >= BOARD_DATA.RED.playerNumberStart){
            draw_player(RED, playerPositions[i]);
        }
        else{
            draw_player(BLUE, playerPositions[i]);
        }
    }
    gfx_SwapDraw();


    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();
    for(int i = 0; i < BOARD_DATA.player_count; i++){//Draw all players
        if(i >= BOARD_DATA.GREEN.playerNumberStart){
            draw_player(GREEN, playerPositions[i]);
        }
        else if(i >= BOARD_DATA.YELLOW.playerNumberStart){
            draw_player(YELLOW, playerPositions[i]);
        }
        else if(i >= BOARD_DATA.RED.playerNumberStart){
            draw_player(RED, playerPositions[i]);
        }
        else{
            draw_player(BLUE, playerPositions[i]);
        }
    }


    //Main Loop
    while(kb_Data[6] != kb_Clear){
        //Testing the move_n_fields() function
        for(int i = 0; i < 7 && kb_Data[6] != kb_Clear; i++){
            
            toClear = playerPositions[0];
            playerPositions[0] = move_n_fields(BLUE, 0, playerPositions[0], (rand() % 6) + 1);

            draw_player(BLUE, playerPositions[0]);
            if(!is_occupied(toClear, playerPositions)){
                redraw_field(toClear);
            }
            gfx_SwapDraw();
            draw_player(BLUE, playerPositions[0]);
            if(!is_occupied(toClear, playerPositions)){
                redraw_field(toClear);
            }
            
            msleep(200);
            kb_Scan();
        }
    }
    gfx_End();
    
}