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

#include <debug.h>

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
            startPoint = BOARD_DATA.BLUE.startPoint;
            h_size = BOARD_DATA.BLUE.h_size;
            h_offset = BOARD_DATA.BLUE.h_offset;
            h_start = BOARD_DATA.BLUE.h_start;
            break;
        case RED:
            startPoint = BOARD_DATA.RED.startPoint;
            h_size = BOARD_DATA.RED.h_size;
            h_offset = BOARD_DATA.RED.h_offset;
            h_start = BOARD_DATA.RED.h_start;
            break;
        case YELLOW:
            startPoint = BOARD_DATA.YELLOW.startPoint;
            h_size = BOARD_DATA.YELLOW.h_size;
            h_offset = BOARD_DATA.YELLOW.h_offset;
            h_start = BOARD_DATA.YELLOW.h_start;
            break;
        case GREEN:
            startPoint = BOARD_DATA.GREEN.startPoint;
            h_size = BOARD_DATA.GREEN.h_size;
            h_offset = BOARD_DATA.GREEN.h_offset;
            h_start = BOARD_DATA.GREEN.h_start;
            break;
    }
    if(position >= 56 && n == 6){//move out of home
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
}

int *move_player(int playerPositions[], int piece_color, int player, int old_position, int n){
    int new_position = move_n_fields(piece_color, player, old_position, n);

    for(int i = 0; i < BOARD_DATA.player_count; i++){
        if(new_position == playerPositions[i] && (i < player / BOARD_DATA.BLUE.h_size || i > player / BOARD_DATA.BLUE.h_size + 3)){
            playerPositions[i] = BOARD_DATA.BLUE.hm_pos + i;
            dbg_printf("TEST");
            return playerPositions;
        }else if(new_position == playerPositions[i] && i >= player / BOARD_DATA.BLUE.h_size && i <= player / BOARD_DATA.BLUE.h_size + 3 && i != player){
            playerPositions[player] = old_position; // dont move
            dbg_printf("TEST");
            return playerPositions;
        }else{
            playerPositions[player] = new_position;
        }
    }
    
    return playerPositions;
}

void draw(int playerPositions[], int toClear){
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    if(!is_occupied(toClear, playerPositions)){
        redraw_field(toClear);
    }
    gfx_SwapDraw();
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    if(!is_occupied(toClear, playerPositions)){
        redraw_field(toClear);
    }
    dbg_printf("%d\n", playerPositions[5]);
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
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    gfx_SwapDraw();


    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();
    draw_player(playerPositions, 0, BOARD_DATA.player_count);

    int player = 0;

    toClear = playerPositions[4];
    *playerPositions = *move_player(playerPositions, RED, 4, playerPositions[4], 6);
    *playerPositions = *move_player(playerPositions, RED, 4, playerPositions[4], 2);
    draw(playerPositions, toClear);
    toClear = playerPositions[5];
    *playerPositions = *move_player(playerPositions, RED, 5, playerPositions[5], 6);
    *playerPositions = *move_player(playerPositions, RED, 5, playerPositions[5], 10);
    draw(playerPositions, toClear);

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        //Testing the move_n_fields() function
        for(int i = 0; i < 7 && kb_Data[6] != kb_Clear; i++){

            /*toClear = playerPositions[player];
            *playerPositions = *move_player(playerPositions, BLUE, player, playerPositions[player], 6);
            draw(playerPositions, toClear);*/
            gfx_SwapDraw();
            
            msleep(500);
            kb_Scan();
        }
    }
    gfx_End();
    
}