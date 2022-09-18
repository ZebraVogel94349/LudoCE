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

void draw_player(int start, int end){
    for(int i = start; i <= end; i++){
        if(i < 4){
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, BLUE);
            gfx_SwapDraw();
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, BLUE);
            gfx_SwapDraw();
        }else if(i < 8){
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, RED);
            gfx_SwapDraw();
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, RED);
            gfx_SwapDraw();
        }else if(i < 12){
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, YELLOW);
            gfx_SwapDraw();
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, YELLOW);
            gfx_SwapDraw();
        }else if(i < 16){
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, GREEN);
            gfx_SwapDraw();
            draw_field(BOARD[PLAYER[i]][0], BOARD[PLAYER[i]][1], 5, GREEN);
            gfx_SwapDraw();
        }
    }
}

void draw_board(){
    for(int i = 0; i < BOARD_DATA.end_of_board + 1; i++){
        connect_fields(BOARD[i][0], BOARD[i][1], BOARD[i + 1][0], BOARD[i + 1][1]);
    }
    connect_fields(BOARD[BOARD_DATA.end_of_board][0], BOARD[BOARD_DATA.end_of_board][1], BOARD[0][0], BOARD[0][1]);
    for(int i = 0; i < 72; i++){
        draw_field(BOARD[i][0], BOARD[i][1], 8, BOARD[i][2]);
    }
}

void redraw_board_part(int start, int end){
    for(int i = start; i <= end; i++){
        if(end <= BOARD_DATA.end_of_board){
            connect_fields(BOARD[i][0], BOARD[i][1], BOARD[i + 1][0], BOARD[i + 1][1]);
        }
        else if(end == BOARD_DATA.end_of_board){
            connect_fields(BOARD[BOARD_DATA.end_of_board][0], BOARD[BOARD_DATA.end_of_board][1], BOARD[0][0], BOARD[0][1]);
        }
    }
    for(int i = start; i <= end + 1; i++){
        draw_field(BOARD[i][0], BOARD[i][1], 8, BOARD[i][2]);
    }
}

void move_n_fields(int piece_color, int player, int n){
    int h_size, h_offset, h_start, hm_pos, hm_out, hm_start, player_group, position;

    switch (piece_color){
        case BLUE:
            hm_pos = BOARD_DATA.BLUE.hm_pos + player;
            hm_out = BOARD_DATA.BLUE.hm_out;
            hm_start = BOARD_DATA.BLUE.hm_start + player;
            h_size = BOARD_DATA.BLUE.h_size;
            h_offset = BOARD_DATA.BLUE.h_offset;
            h_start = BOARD_DATA.BLUE.h_start;
            position = PLAYER[hm_start];
            player_group = 0;
            break;
        case RED:
            hm_pos = BOARD_DATA.RED.hm_pos + player;
            hm_out = BOARD_DATA.RED.hm_out;
            hm_start = BOARD_DATA.RED.hm_start + player;
            h_size = BOARD_DATA.RED.h_size;
            h_offset = BOARD_DATA.RED.h_offset;
            h_start = BOARD_DATA.RED.h_start;
            position = PLAYER[hm_start];
            player_group = 4;
            break;
        case YELLOW:
            hm_pos = BOARD_DATA.YELLOW.hm_pos + player;
            hm_out = BOARD_DATA.YELLOW.hm_out;
            hm_start = BOARD_DATA.YELLOW.hm_start + player;
            h_size = BOARD_DATA.YELLOW.h_size;
            h_offset = BOARD_DATA.YELLOW.h_offset;
            h_start = BOARD_DATA.YELLOW.h_start;
            position = PLAYER[hm_start];
            player_group = 8;
            break;
        case GREEN:
            hm_pos = BOARD_DATA.GREEN.hm_pos + player;
            hm_out = BOARD_DATA.GREEN.hm_out;
            hm_start = BOARD_DATA.GREEN.hm_start + player;
            h_size = BOARD_DATA.GREEN.h_size;
            h_offset = BOARD_DATA.GREEN.h_offset;
            h_start = BOARD_DATA.GREEN.h_start;
            position = PLAYER[hm_start];
            player_group = 12;
            break;
    }

    if(PLAYER[hm_start] == hm_pos && n == 6){//move outside home
        PLAYER[hm_start] = hm_out;
    }
    else if(position <= h_offset && position + n > h_offset && position + n <= h_offset + h_size){//move into house
        PLAYER[hm_start] = h_start + (position + n - (h_offset + 1));
    }
    else if(position <= h_offset && position + n > h_offset){//dont move
        PLAYER[hm_start] = PLAYER[hm_start];
    }
    else if((position >= h_start && position + n < h_start + h_size)){//move inside house
        PLAYER[hm_start] = position + n;
    }
    else if(position + n <= BOARD_DATA.end_of_board){//move normally
        PLAYER[hm_start] = position + n;
    }
    else if(position <= BOARD_DATA.end_of_board){//go from end of board to 0
        PLAYER[hm_start] = position + n - (BOARD_DATA.end_of_board + 1);
    }

    // throw out or scip player
    for(int i = 0; i < (int)sizeof(PLAYER); i++){
        if(PLAYER[hm_start] == PLAYER[i] && (i < player_group || i > player_group + 3)){
            PLAYER[i] = BOARD_DATA.BLUE.hm_pos + i;
            
            // redraw player in home
            draw_player(i, i);
            break;
        }else if(PLAYER[hm_start] == PLAYER[i] && i >= player_group && i <= player_group + 3 && i != player_group + player){
            PLAYER[hm_start] = position; // dont move
            break;
        }
    }

    if(PLAYER[hm_start] != position){
        // redraw board part
        redraw_board_part(position, position - 1);
        gfx_SwapDraw();
        redraw_board_part(position, position - 1);
        gfx_SwapDraw();

        // redraw old player pos
        draw_player(player_group + player, player_group + player);
    }
}


int main(){
    gfx_Begin();
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0);
    gfx_SetDrawBuffer();
    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();    
    gfx_SwapDraw();
    gfx_FillScreen(BACKGROUND_YELLOW);
    draw_board();
    draw_player(0, BOARD_DATA.end_of_home);

    msleep(100);

    //move_n_fields(BLUE, 1, 6);
    move_n_fields(BLUE, 0, 6);
    move_n_fields(BLUE, 0, 40);
    move_n_fields(BLUE, 1, 6);

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        //Testing the move_n_fields() function
        for(int i = 0; i < 7 && kb_Data[6] != kb_Clear; i++){
            move_n_fields(BLUE, 1, 1);
            msleep(200);
            kb_Scan();
        }
        //Testing the redraw_board_part() function
        /*redraw_board_part(0,7);
        gfx_SwapDraw();
        redraw_board_part(0,7);
        gfx_SwapDraw();
        kb_Scan();*/
    }
    gfx_End();
    
}