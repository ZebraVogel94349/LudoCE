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
    //Move forwards, if there is no way to reach the house
    if(position + n < 40 && 
        (position < 4 || 
        (position > 9 && position < 14) ||
        (position > 19 && position < 24) ||
        (position > 29 && position < 34) ||
        (piece_color != RED && (position > 3 && position < 10)) ||
        (piece_color != YELLOW && (position > 13 && position < 20)) ||
        (piece_color != GREEN && (position > 23 && position < 30)) ||
        (piece_color != BLUE && (position > 33 && position < 40)))
      ){
        return position + n;
    }
    else if(position + n > 39 && position < 40 && piece_color != BLUE){//go from 39 to 0
        return n - 1;
    }
    //Move blue into or inside the house
    else if(piece_color == BLUE && (position > 33 && position < 44)){
        if(position + n < 44){
            return position + n;
        }
        else{
            return 255;
        }
    }
    //Move red before, into or inside the house
    else if(piece_color == RED && (position > 3 && position < 10)){
        if(position + n + 34 > 43 && position + n + 34 < 48){
            return position + n + 34;
        }
        else if(position + n < 10){
            return position + n;
        }
        else{
            return 255;
        }
    }
    else if(piece_color == RED && (position > 43 && position < 48)){
        if(position + n < 48){
            return position + n;
        }
        else{
            return 255;
        }
    }
    //Move yellow before, into or inside the house
    else if(piece_color == YELLOW && (position > 13 && position < 20)){
        if(position + n + 28 > 47 && position + n + 28 < 52){
            return position + n + 28;
        }
        else if(position + n < 20){
            return position + n;
        }
        else{
            return 255;
        }
    }
    else if(piece_color == YELLOW && (position > 47 && position < 52)){
        if(position + n < 52){
            return position + n;
        }
        else{
            return 255;
        }
    }
    //Move green before, into or inside the house
    else if(piece_color == GREEN && (position > 23 && position < 30)){
        if(position + n + 22 > 51 && position + n + 22 < 56){
            return position + n + 22;
        }
        else if(position + n < 30){
            return position + n;
        }
        else{
            return 255;
        }
    }
    else if(piece_color == GREEN && (position > 51 && position < 56)){
        if(position + n < 56){
            return position + n;
        }
        else{
            return 255;
        }
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

        for(int i = 0; i < 20; i++){
            draw_board();
            draw_field(BOARD[pos][0], BOARD[pos][1], BLACK);
            gfx_SwapDraw();
            draw_board();
            draw_field(BOARD[pos][0], BOARD[pos][1], BLACK);
            gfx_SwapDraw();
            pos = move_n_fields(pos, 6, RED);
            msleep(200);
        }

        kb_Scan();
    }
    gfx_End();
    
}
