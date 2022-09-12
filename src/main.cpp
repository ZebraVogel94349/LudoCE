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

void draw_field(int x, int y, int color){
    gfx_SetColor(BLACK);
    gfx_FillCircle_NoClip(x + 10, y + 10, 8);
    gfx_SetColor(color);
    gfx_FillCircle_NoClip(x + 10, y + 10, 7);
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
        draw_field(BOARD[i][0], BOARD[i][1], BOARD[i][2]);
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
        draw_field(BOARD[i][0], BOARD[i][1], BOARD[i][2]);
    }
    
    

}

int move_n_fields(int position, int n, int piece_color){
    int h_size, h_offset, h_start;

    switch (piece_color){
        case BLUE:
            h_size = BOARD_DATA.BLUE.h_size;
            h_offset = BOARD_DATA.BLUE.h_offset;
            h_start = BOARD_DATA.BLUE.h_start;
            break;
        case RED:
            h_size = BOARD_DATA.RED.h_size;
            h_offset = BOARD_DATA.RED.h_offset;
            h_start = BOARD_DATA.RED.h_start;
            break;
        case YELLOW:
            h_size = BOARD_DATA.YELLOW.h_size;
            h_offset = BOARD_DATA.YELLOW.h_offset;
            h_start = BOARD_DATA.YELLOW.h_start;
            break;
        case GREEN:
            h_size = BOARD_DATA.GREEN.h_size;
            h_offset = BOARD_DATA.GREEN.h_offset;
            h_start = BOARD_DATA.GREEN.h_start;
            break;
    }

    if(position + n + h_offset >= h_start && position + n + h_offset < h_start + h_size){//move into house
        return position + n + h_offset;
    }
    else if((position >= h_start && position + n < h_start + h_size)){//move inside house
        return position + n;
    }
    else if(position + n <= BOARD_DATA.end_of_board){//move normally
        return position + n;
    }
    else if(position <= BOARD_DATA.end_of_board){//go from end of board to 0
        return n - 1;
    }
    else{
        return 255;
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

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        int pos = 0;

        //Testing the move_n_fields() function
        for(int i = 0; i < 45 && kb_Data[6] != kb_Clear; i++){
            draw_field(BOARD[pos][0], BOARD[pos][1], GREEN);
            gfx_SwapDraw();
            draw_field(BOARD[pos][0], BOARD[pos][1], GREEN);
            gfx_SwapDraw();
            pos = move_n_fields(pos, 1, BLUE);
            msleep(100);
            kb_Scan();
        }
        //Testing the redraw_board_part() function
        redraw_board_part(0,7);
        gfx_SwapDraw();
        redraw_board_part(0,7);
        gfx_SwapDraw();
        kb_Scan();
    }
    gfx_End();
    
}