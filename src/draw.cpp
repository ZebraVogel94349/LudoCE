#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include "gfx/colors.h"
#include "gfx/gfx.h"
#include "const.h"
#include "draw.hpp"
#include "game.hpp"

void start_die_animation(int n){
    if(n == 1){
        gfx_Sprite_NoClip(die_1, 150, 110);
    }
    else if(n == 2){
        gfx_Sprite_NoClip(die_2, 150, 110);
    }
    else if(n == 3){   
        gfx_Sprite_NoClip(die_3, 150, 110);
    }
    else if(n == 4){
        gfx_Sprite_NoClip(die_4, 150, 110);
    }
    else if(n == 5){
        gfx_Sprite_NoClip(die_5, 150, 110);
    }
    else if(n == 6){
        gfx_Sprite_NoClip(die_6, 150, 110);
    }
    gfx_BlitBuffer();
}

void draw_field(int x, int y, int r, int color){
    gfx_SetColor(BLACK);
    gfx_FillCircle_NoClip(x + r, y + r, r);
    gfx_SetColor(color);
    gfx_FillCircle_NoClip(x + r, y + r, r - 1);
}

void draw_field_pos(int position, int boardType){
    draw_field(BOARD[boardType][position][0], BOARD[boardType][position][1], BOARD_DATA[boardType][5], BOARD[boardType][position][2]);
}

void connect_fields(int x0, int y0, int x1, int y1, int r){
    gfx_SetColor(BLACK);
    gfx_Line(x0 + r, y0 + r, x1 + r, y1 + r);
}

void draw_board(int boardType){
    for(int i = 0; i < BOARD_DATA[boardType][1]; i++){
        connect_fields(BOARD[boardType][i][0], BOARD[boardType][i][1], BOARD[boardType][i + 1][0], BOARD[boardType][i + 1][1], BOARD_DATA[boardType][5]);
    }
    connect_fields(BOARD[boardType][BOARD_DATA[boardType][1]][0], BOARD[boardType][BOARD_DATA[boardType][1]][1], BOARD[boardType][0][0], BOARD[boardType][0][1], 7);
    for(int i = 0; i < BOARD_DATA[boardType][3]; i++){
        draw_field_pos(i, boardType);
    }
}

void draw_player(int playerPositions[], int start, int end, int boardType){
    for(int i = start; i < end; i++){
        if(playerPositions[i] != -1){
            draw_field(BOARD[boardType][playerPositions[i]][0] + 3, BOARD[boardType][playerPositions[i]][1] + 3, BOARD_DATA[boardType][5] - 3, get_color(i, boardType));
        }
    }
}

void draw_name(int playerTypes[], int playerIndicator, int boardType){
    char names[2][6][5] = {{"P1", "P2", "P3", "P4", "P5", "P6"}, {"B1", "B2", "B3", "B4", "B5", "B6"}};
    int pb[2] = {0, 0};
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[boardType][0][0], BOARD_PLAYER_NAMING[boardType][0][1], 20, 15);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[boardType][1][0], BOARD_PLAYER_NAMING[boardType][1][1], 20, 15);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[boardType][2][0], BOARD_PLAYER_NAMING[boardType][2][1], 20, 15);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[boardType][3][0], BOARD_PLAYER_NAMING[boardType][3][1], 20, 15);
    if(boardType == 1){
        gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[boardType][4][0], BOARD_PLAYER_NAMING[boardType][4][1], 20, 15);
        gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[boardType][5][0], BOARD_PLAYER_NAMING[boardType][5][1], 20, 15);
    }
    for(int i = 0; i < BOARD_DATA[boardType][0] / BOARD_DATA[boardType][2]; i++){
        if(playerTypes[i] != 2){
            int width = gfx_GetStringWidth(names[playerTypes[i] != 0][pb[playerTypes[i] == 0]]);
            gfx_PrintStringXY(names[playerTypes[i] != 0][pb[playerTypes[i] == 0]], BOARD_PLAYER_NAMING[boardType][i][0] + 2, BOARD_PLAYER_NAMING[boardType][i][1] + 2);

            gfx_SetColor(BLACK);
            if(i == (playerIndicator - 2)){
                gfx_Rectangle_NoClip(BOARD_PLAYER_NAMING[boardType][i][0], BOARD_PLAYER_NAMING[boardType][i][1], width + 3, 12);
            }
            pb[playerTypes[i] == 0]++;
        }
    }
}

void draw_everything(int playerTypes[], int playerPositions[], int toClear, int playerIndicator, int boardType){
    if(occupied_by(toClear, playerPositions, boardType) == -1){
        draw_field_pos(toClear, boardType);
    }
    draw_player(playerPositions, 0, BOARD_DATA[boardType][0], boardType);
    draw_name(playerTypes, playerIndicator, boardType);
    
    gfx_BlitBuffer();
}

void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection, int boardType){
    draw_field_pos(playerPositions[oldSelection], boardType);
    draw_field(BOARD[boardType][playerPositions[selectedPlayer]][0], BOARD[boardType][playerPositions[selectedPlayer]][1], BOARD_DATA[boardType][5], BLACK);
}

void draw_potential_field(int selectedField, int oldField, int boardType){
    draw_field_pos(oldField, boardType);
    draw_field(BOARD[boardType][selectedField][0], BOARD[boardType][selectedField][1], BOARD_DATA[boardType][5], LIGHT_GREEN);
}