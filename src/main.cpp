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

void draw_field(int x, int y, int color){
    gfx_SetColor(BLACK);
    gfx_FillCircle_NoClip(x + 10, y + 10, 10);
    gfx_SetColor(color);
    gfx_FillCircle_NoClip(x + 10, y + 10, 9);
}

void draw_board(){
    int board[1][3] = {{0, 0, BLUE}};
    for(int i = 0; i < 1; i++){
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
