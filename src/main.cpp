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

int occupied_by(int position, int playerPositions[]){
    for(int i = 0; i < BOARD_DATA.player_count; i++){
        if(playerPositions[i] == position){
            return i;
        }
    }
    return -1;
}

int move_n_fields(int piece_color, int position, int n){
    int h_offset, h_start, startPoint;

    switch (piece_color){
        case BLUE:
            startPoint = BOARD_DATA.BLUE.startPoint;
            h_offset = BOARD_DATA.BLUE.h_offset;
            h_start = BOARD_DATA.BLUE.h_start;
            break;
        case RED:
            startPoint = BOARD_DATA.RED.startPoint;
            h_offset = BOARD_DATA.RED.h_offset;
            h_start = BOARD_DATA.RED.h_start;
            break;
        case YELLOW:
            startPoint = BOARD_DATA.YELLOW.startPoint;
            h_offset = BOARD_DATA.YELLOW.h_offset;
            h_start = BOARD_DATA.YELLOW.h_start;
            break;
        case GREEN:
            startPoint = BOARD_DATA.GREEN.startPoint;
            h_offset = BOARD_DATA.GREEN.h_offset;
            h_start = BOARD_DATA.GREEN.h_start;
            break;
    }
    if(position >= 56 && n == 6){//move out of home
        return startPoint;
    }
    else if(position <= h_offset && position + n > h_offset && position + n <= h_offset + BOARD_DATA.h_size){//move into house
        return h_start + (position + n - (h_offset + 1));
    }
    else if(position <= h_offset && position + n > h_offset){//dont move if you cant move any further
        return position;
    }

    else if((position >= h_start && position + n < h_start + BOARD_DATA.h_size)){//move inside house
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

int get_color(int playerNumber){
    if(playerNumber >= BOARD_DATA.GREEN.playerNumberStart){
        return GREEN;
    }
    else if(playerNumber >= BOARD_DATA.YELLOW.playerNumberStart){
        return YELLOW;
    }
    else if(playerNumber >= BOARD_DATA.RED.playerNumberStart){
        return RED;
    }
    else{
        return BLUE;
    }
}

int *move_player(int playerPositions[], int piece_color, int player, int old_position, int n){
    int new_position = move_n_fields(piece_color, old_position, n);
    int occupyingPlayer = occupied_by(new_position, playerPositions);
    if(occupyingPlayer == -1){
        playerPositions[player] = new_position;
        return playerPositions;
    }
    else if(new_position == playerPositions[occupyingPlayer] && (get_color(player) != get_color(occupyingPlayer))){//throw out
        playerPositions[occupyingPlayer] = BOARD_DATA.BLUE.hm_pos + occupyingPlayer;
        playerPositions[player] = new_position;
        return playerPositions;
    }    
    else{
        return playerPositions;//don't move if field is occupied by own player
    }
    
    
}

void draw(int playerPositions[], int toClear, int color, int number){
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    if(occupied_by(toClear, playerPositions) == -1){
        redraw_field(toClear);
    }
    gfx_SwapDraw();
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    if(occupied_by(toClear, playerPositions) == -1){
        redraw_field(toClear);
    }
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    gfx_SetTextFGColor(color);
    gfx_SetTextXY(6,6);
    gfx_PrintInt(number, 1);
}

int *move_enemy(int playerPositions[], int piece_color, int n){
    int hm_pos, playerNumberStart, occupyingPlayer, startPoint;
    bool allOut = true;
    if(piece_color == BLUE){
        hm_pos = BOARD_DATA.BLUE.hm_pos;
        playerNumberStart = BOARD_DATA.BLUE.playerNumberStart;
        startPoint = BOARD_DATA.BLUE.startPoint;
    }
    else if(piece_color == RED){
        hm_pos = BOARD_DATA.RED.hm_pos;
        playerNumberStart = BOARD_DATA.RED.playerNumberStart;
        startPoint = BOARD_DATA.RED.startPoint;
    }
    else if(piece_color == YELLOW){
        hm_pos = BOARD_DATA.RED.hm_pos;
        playerNumberStart = BOARD_DATA.YELLOW.playerNumberStart;
        startPoint = BOARD_DATA.YELLOW.startPoint;
    }
    else{
        hm_pos = BOARD_DATA.GREEN.hm_pos;
        playerNumberStart = BOARD_DATA.GREEN.playerNumberStart;
        startPoint = BOARD_DATA.GREEN.startPoint;
    }

    occupyingPlayer = occupied_by(startPoint, playerPositions);
    if(occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color){
        for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
            if(n == 6 && playerPositions[i] >= hm_pos){
                playerPositions[16] = playerPositions[i];
                playerPositions = move_player(playerPositions, piece_color, i, playerPositions[i], n);//move player out of home if you have to 
                return playerPositions;
            }
        }
    }
    
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        if(playerPositions[i] >= hm_pos){
            allOut = false;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] == startPoint && (occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color) && !allOut){
            playerPositions[16] = playerPositions[i];
            playerPositions = move_player(playerPositions, piece_color, i, playerPositions[i], n);//move player from start point if you have to
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer != -1 && get_color(occupyingPlayer) != piece_color && rand() % 10 != 0){
            playerPositions[16] = playerPositions[i];
            playerPositions = move_player(playerPositions, piece_color, i, playerPositions[i], n);//throw out player
            return playerPositions;
        }
    }
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer == -1 && (rand() % 4 != 0 || i == playerNumberStart - 1) && move_n_fields(piece_color, playerPositions[i], n) != playerPositions[i]){
            playerPositions[16] = playerPositions[i];
            playerPositions = move_player(playerPositions, piece_color, i, playerPositions[i], n);//move player to empty field
            return playerPositions;
        }
    }
    return playerPositions;
}

int main(){
    int playerPositions[17] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 27};
    int toClear = 0;
    int r = 1;
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

    //Main Loop
    while(kb_Data[6] != kb_Clear){
        //Testing the move_enemy() function
        for(int i = 2; i < 6 && kb_Data[6] != kb_Clear; i++){
            r = rand() % 6 + 1;
            *playerPositions = *move_enemy(playerPositions, i, r);
            toClear = playerPositions[16];
            draw(playerPositions, toClear, i, r);
            if(r == 6){i--;}
            gfx_SwapDraw();


            msleep(2000);
            kb_Scan();
        }
    }
    gfx_End();
    
}