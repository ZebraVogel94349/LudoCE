#include "graphx.h"
#include "gfx/colors.h"
#include "const.h"
#include "draw.hpp"
#include "game.hpp"

void draw_field(int x, int y, int r, int color){
    gfx_SetColor(BLACK);
    gfx_FillCircle_NoClip(x + 10, y + 10, r);
    gfx_SetColor(color);
    gfx_FillCircle_NoClip(x + 10, y + 10, r - 1);
}

void draw_field_pos(int position){
    draw_field(BOARD[position][0], BOARD[position][1], 8, BOARD[position][2]);
}

void connect_fields(int x0, int y0, int x1, int y1){
    gfx_SetColor(BLACK);
    gfx_Line(x0 + 10, y0 + 10, x1 + 10, y1 + 10);
}

void draw_board(){
    for(int i = 0; i < BOARD_DATA[1]; i++){
        connect_fields(BOARD[i][0], BOARD[i][1], BOARD[i + 1][0], BOARD[i + 1][1]);
    }
    connect_fields(BOARD[BOARD_DATA[1]][0], BOARD[BOARD_DATA[1]][1], BOARD[0][0], BOARD[0][1]);
    for(int i = 0; i < BOARD_DATA[3]; i++){
        draw_field_pos(i);
    }
}

void draw_player(int playerPositions[], int start, int end){
    for(int i = start; i < end; i++){
        draw_field(BOARD[playerPositions[i]][0], BOARD[playerPositions[i]][1], 5, get_color(i));
    }
}

void draw_everything(int playerPositions[], int toClear, int color, int number){
    if(occupied_by(toClear, playerPositions) == -1){
        draw_field_pos(toClear);
    }
    draw_player(playerPositions, 0, BOARD_DATA[0]);
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    if(number != 0){
        gfx_SetTextFGColor(BLACK);
        gfx_SetTextXY(6,6);
        gfx_PrintInt(number, 1);
    }
    
    gfx_SwapDraw();

    if(occupied_by(toClear, playerPositions) == -1){
        draw_field_pos(toClear);
    }
    draw_player(playerPositions, 0, BOARD_DATA[0]);
    draw_field_pos(toClear);
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    if(number != 0){
        gfx_SetTextFGColor(BLACK);
        gfx_SetTextXY(6,6);
        gfx_PrintInt(number, 1);
    }
}

void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection){
    draw_field_pos(playerPositions[oldSelection]);
    draw_field(BOARD[playerPositions[selectedPlayer]][0], BOARD[playerPositions[selectedPlayer]][1], 7, BLACK);
}

void draw_potential_field(int selectedField, int oldField){
    draw_field_pos(oldField);
    draw_field(BOARD[selectedField][0], BOARD[selectedField][1], 8, LIGHT_GREEN);
}