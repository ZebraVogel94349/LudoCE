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

void draw_board(){
    for(int i = 0; i < 72; i++){
        draw_field(BOARD[i][0], BOARD[i][1], BOARD[i][2]);
    }
}

int move_n_fields(int position, int n, int piece_color){
    const int *h_size, *h_offset, *h_start;

    switch (piece_color){
        case BLUE:
            h_size = &BOARD_DATA.BLUE.h_size;
            h_offset = &BOARD_DATA.BLUE.h_offset;
            h_start = &BOARD_DATA.BLUE.h_start;
            break;
        case RED:
            h_size = &BOARD_DATA.RED.h_size;
            h_offset = &BOARD_DATA.RED.h_offset;
            h_start = &BOARD_DATA.RED.h_start;
            break;
        case YELLOW:
            h_size = &BOARD_DATA.YELLOW.h_size;
            h_offset = &BOARD_DATA.YELLOW.h_offset;
            h_start = &BOARD_DATA.YELLOW.h_start;
            break;
        case GREEN:
            h_size = &BOARD_DATA.GREEN.h_size;
            h_offset = &BOARD_DATA.GREEN.h_offset;
            h_start = &BOARD_DATA.GREEN.h_start;
            break;
    }

    if(position + n + *h_offset >= *h_start && position + n + *h_offset < *h_start + *h_size){//move into house
        return position + n + *h_offset;
    }
    else if((position >= *h_start && position + n < *h_start + *h_size)){//move inside house
        return position + n;
    }
    else if(position + n < BOARD_DATA.end_of_board){//move normally
        return position + n;
    }
    else if(position < BOARD_DATA.end_of_board){//go from 39 to 0
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
    gfx_SwapDraw();
    gfx_FillScreen(BACKGROUND_YELLOW);

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        draw_board();
        int pos = 0;

        //Testing the move_n_fields() function
        for(int i = 0; i < 100; i++){
            draw_board();
            draw_field(BOARD[pos][0], BOARD[pos][1], BLACK);
            gfx_SwapDraw();
            draw_board();
            draw_field(BOARD[pos][0], BOARD[pos][1], BLACK);
            gfx_SwapDraw();
            pos = move_n_fields(pos, 1, BLUE);
            msleep(100);
        }

        kb_Scan();
    }
    gfx_End();
    
}
