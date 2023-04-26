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

void draw_field_pos(int position, const int (*BOARD)[3], const int* BOARD_DATA){
    draw_field(BOARD[position][0], BOARD[position][1], BOARD_DATA[5], BOARD[position][2]);
}

void connect_fields(int x0, int y0, int x1, int y1, int r){
    gfx_SetColor(BLACK);
    gfx_Line(x0 + r, y0 + r, x1 + r, y1 + r);
}

void draw_board(const int (*BOARD)[3], const int* BOARD_DATA){
    for(int i = 0; i < BOARD_DATA[1]; i++){
        connect_fields(BOARD[i][0], BOARD[i][1], BOARD[i + 1][0], BOARD[i + 1][1], BOARD_DATA[5]);
    }
    connect_fields(BOARD[BOARD_DATA[1]][0], BOARD[BOARD_DATA[1]][1], BOARD[0][0], BOARD[0][1], 7);
    for(int i = 0; i < BOARD_DATA[3]; i++){
        draw_field_pos(i, BOARD, BOARD_DATA);
    }
}

void draw_player(int playerPositions[], int start, int end, const int (*BOARD)[3], const int* BOARD_DATA){
    for(int i = start; i < end; i++){
        if(playerPositions[i] != -1){
            draw_field(BOARD[playerPositions[i]][0] + 3, BOARD[playerPositions[i]][1] + 3, BOARD_DATA[5] - 3, get_color(i, BOARD_DATA));
        }
    }
}

void draw_name(int playerTypes[], int playerIndicator, const int* BOARD_DATA, const int (*BOARD_PLAYER_NAMING)[2], int boardType){
    char names[2][6][5] = {{"P1", "P2", "P3", "P4", "P5", "P6"}, {"B1", "B2", "B3", "B4", "B5", "B6"}};
    int pb[2] = {0, 0};
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[0][0], BOARD_PLAYER_NAMING[0][1], 20, 15);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[1][0], BOARD_PLAYER_NAMING[1][1], 20, 15);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[2][0], BOARD_PLAYER_NAMING[2][1], 20, 15);
    gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[3][0], BOARD_PLAYER_NAMING[3][1], 20, 15);
    if(boardType == 1){
        gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[4][0], BOARD_PLAYER_NAMING[4][1], 20, 15);
        gfx_FillRectangle_NoClip(BOARD_PLAYER_NAMING[5][0], BOARD_PLAYER_NAMING[5][1], 20, 15);
    }
    for(int i = 0; i < BOARD_DATA[0] / BOARD_DATA[2]; i++){
        if(playerTypes[i] != 2){
            int width = gfx_GetStringWidth(names[playerTypes[i] != 0][pb[playerTypes[i] == 0]]);
            gfx_PrintStringXY(names[playerTypes[i] != 0][pb[playerTypes[i] == 0]], BOARD_PLAYER_NAMING[i][0] + 2, BOARD_PLAYER_NAMING[i][1] + 2);

            gfx_SetColor(BLACK);
            if(i == (playerIndicator - 2)){
                gfx_Rectangle_NoClip(BOARD_PLAYER_NAMING[i][0], BOARD_PLAYER_NAMING[i][1], width + 3, 12);
            }
            pb[playerTypes[i] == 0]++;
        }
    }
}

void draw_everything(int playerTypes[], int playerPositions[], int toClear, int playerIndicator, const int (*BOARD)[3], const int* BOARD_DATA, const int (*BOARD_PLAYER_NAMING)[2], int boardType){
    if(toClear != -1 && occupied_by(toClear, playerPositions, BOARD_DATA) == -1){
        draw_field_pos(toClear, BOARD, BOARD_DATA);
    }
    draw_player(playerPositions, 0, BOARD_DATA[0], BOARD, BOARD_DATA);
    draw_name(playerTypes, playerIndicator, BOARD_DATA, BOARD_PLAYER_NAMING, boardType);
    
    gfx_BlitBuffer();
}

void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection, const int (*BOARD)[3], const int* BOARD_DATA){
    draw_field_pos(playerPositions[oldSelection], BOARD, BOARD_DATA);
    draw_field(BOARD[playerPositions[selectedPlayer]][0], BOARD[playerPositions[selectedPlayer]][1], BOARD_DATA[5], BLACK);
}

void draw_potential_field(int selectedField, int oldField, const int (*BOARD)[3], const int* BOARD_DATA){
    draw_field_pos(oldField, BOARD, BOARD_DATA);
    draw_field(BOARD[selectedField][0], BOARD[selectedField][1], BOARD_DATA[5], LIGHT_GREEN);
}