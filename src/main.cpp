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
#include "gfx/vars.h"

void draw_field(int x, int y, int color){
    gfx_SetColor(BLACK);
    gfx_FillCircle_NoClip(x + 10, y + 10, 8);
    gfx_SetColor(color);
    gfx_FillCircle_NoClip(x + 10, y + 10, 7);
}

void draw_board(){
    int board[72][3] = {{left_margin, top_margin, GREEN}, {left_margin + 21, top_margin, GREEN}, {left_margin, top_margin + 21, GREEN}, {left_margin + 21, top_margin + 21, GREEN}, 
                       {left_margin + 189, top_margin, BLUE}, {left_margin + 210, top_margin, BLUE}, {left_margin + 189, top_margin + 21, BLUE}, {left_margin + 210, top_margin + 21, BLUE},
                       {left_margin + 189, top_margin + 189, RED}, {left_margin + 210, top_margin + 189, RED}, {left_margin + 189, top_margin + 210, RED}, {left_margin + 210, top_margin + 210, RED},
                       {left_margin, top_margin + 189, YELLOW}, {left_margin + 21, top_margin + 189, YELLOW}, {left_margin, top_margin + 210, YELLOW}, {left_margin + 21, top_margin + 210, YELLOW},
                       {left_margin + 84, top_margin, BACKGROUND_YELLOW}, {left_margin + 105, top_margin, BACKGROUND_YELLOW}, {left_margin + 126, top_margin, BLUE},
                       {left_margin + 84, top_margin + 21, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 21, BLUE}, {left_margin + 126, top_margin + 21, BACKGROUND_YELLOW},
                       {left_margin + 84, top_margin + 42, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 42, BLUE}, {left_margin + 126, top_margin + 42, BACKGROUND_YELLOW},
                       {left_margin + 84, top_margin + 63, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 63, BLUE}, {left_margin + 126, top_margin + 63, BACKGROUND_YELLOW},
                       {left_margin, top_margin + 84, GREEN}, {left_margin + 21, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 42, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 63, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 84, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 84, BLUE}, {left_margin + 126, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 147, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 168, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 189, top_margin + 84, BACKGROUND_YELLOW}, {left_margin + 210, top_margin + 84, BACKGROUND_YELLOW},
                       {left_margin, top_margin + 105, BACKGROUND_YELLOW}, {left_margin + 21, top_margin + 105, GREEN}, {left_margin + 42, top_margin + 105, GREEN}, {left_margin + 63, top_margin + 105, GREEN}, {left_margin + 84, top_margin + 105, GREEN}, {left_margin + 126, top_margin + 105, RED}, {left_margin + 147, top_margin + 105, RED}, {left_margin + 168, top_margin + 105, RED}, {left_margin + 189, top_margin + 105, RED}, {left_margin + 210, top_margin + 105, BACKGROUND_YELLOW},
                       {left_margin, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 21, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 42, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 63, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 84, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 126, YELLOW}, {left_margin + 126, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 147, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 168, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 189, top_margin + 126, BACKGROUND_YELLOW}, {left_margin + 210, top_margin + 126, RED},
                       {left_margin + 84, top_margin + 147, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 147, YELLOW}, {left_margin + 126, top_margin + 147, BACKGROUND_YELLOW},
                       {left_margin + 84, top_margin + 168, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 168, YELLOW}, {left_margin + 126, top_margin + 168, BACKGROUND_YELLOW},
                       {left_margin + 84, top_margin + 189, BACKGROUND_YELLOW}, {left_margin + 105, top_margin + 189, YELLOW}, {left_margin + 126, top_margin + 189, BACKGROUND_YELLOW},
                       {left_margin + 84, top_margin + 210, YELLOW}, {left_margin + 105, top_margin + 210, BACKGROUND_YELLOW}, {left_margin + 126, top_margin + 210, BACKGROUND_YELLOW}};
    for(int i = 0; i < 72; i++){
        draw_field(board[i][0], board[i][1], board[i][2]);
    }
}

int main(){
    gfx_Begin();
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0);
    gfx_SetDrawBuffer();
    gfx_FillScreen(1);
    gfx_SwapDraw();
    gfx_FillScreen(1);

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        draw_board();
        gfx_SwapDraw();
        kb_Scan();
    }
    gfx_End();
    
}
