#include <tice.h>
#include <keypadc.h>
#include <fileioc.h>
#include <graphx.h>

#include "gfx/palette_gfx.h"
#include "gfx/colors.h"
#include "const.h"

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
    else if(playerNumber >= BOARD_DATA.BLUE.playerNumberStart){
        return BLUE;
    }else{
        return -1;
    }
}

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
        draw_field(BOARD[playerPositions[i]][0], BOARD[playerPositions[i]][1], 5, get_color(i));
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

int *throw_out(int playerPositions[], int piece_color, int player, int old_position, int n){
    int new_position = move_n_fields(piece_color, old_position, n);
    int occupyingPlayer = occupied_by(new_position, playerPositions);
    
    playerPositions[occupyingPlayer] = BOARD_DATA.BLUE.hm_pos + occupyingPlayer;
    playerPositions[player] = new_position;
    return playerPositions;
}

int check_for_order(int playerPositions[], int piece_color){
    int h_start, playerNumberStart;
    bool houseFieldIsOccupied = true;
    int fields = 0;
    if(piece_color == BLUE){
        h_start = BOARD_DATA.BLUE.h_start;
        playerNumberStart = BOARD_DATA.BLUE.playerNumberStart;
    }
    else if(piece_color == RED){
        h_start = BOARD_DATA.RED.h_start;
        playerNumberStart = BOARD_DATA.RED.playerNumberStart;
    }
    else if(piece_color == YELLOW){
        h_start = BOARD_DATA.YELLOW.h_start;
        playerNumberStart = BOARD_DATA.YELLOW.playerNumberStart;
    }
    else{
        h_start = BOARD_DATA.GREEN.h_start;
        playerNumberStart = BOARD_DATA.GREEN.playerNumberStart;
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        if(playerPositions[i] < h_start){//if player on the field
            return false;
        }
        else if(playerPositions[i] >= BOARD_DATA.BLUE.hm_pos){//one more player in home
            fields++;
        }
    }
    if(fields == 4){//if all players in home
        return true;
    }
    else{
        fields = 0;//otherwise reset fields
    }

    for(int j = 1; j < BOARD_DATA.h_size; j++){
        for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
            if(playerPositions[i] == h_start + BOARD_DATA.h_size - j){
                houseFieldIsOccupied = true;
                fields++;
                break;
            }
            else{
                houseFieldIsOccupied = false;
            }
        }
        if(!houseFieldIsOccupied && fields == 0){//no player on the last house field
            return false;
        }
        else if(houseFieldIsOccupied && fields != j){//no order
            return false;
        }
    }
    return true;
}

void draw(int playerPositions[], int toClear, int color, int number){
    if(occupied_by(toClear, playerPositions) == -1){
        redraw_field(toClear);
    }
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    if(number != 0){
        gfx_SetTextFGColor(BLACK);
        gfx_SetTextXY(6,6);
        gfx_PrintInt(number, 1);
    }
    
    
    gfx_SwapDraw();

    if(occupied_by(toClear, playerPositions) == -1){
        redraw_field(toClear);
    }
    draw_player(playerPositions, 0, BOARD_DATA.player_count);
    redraw_field(toClear);
    gfx_SetColor(BACKGROUND_YELLOW);
    gfx_FillRectangle_NoClip(5,5,20,20);
    if(number != 0){
        gfx_SetTextFGColor(BLACK);
        gfx_SetTextXY(6,6);
        gfx_PrintInt(number, 1);
    }
}

void draw_player_selection(int *playerPositions, int selectedPlayer, int oldSelection){
    redraw_field(playerPositions[oldSelection]);
    draw_field(BOARD[playerPositions[selectedPlayer]][0], BOARD[playerPositions[selectedPlayer]][1], 7, BLACK);
}

void draw_potential_field(int selectedField, int oldField){
    redraw_field(oldField);
    draw_field(BOARD[selectedField][0], BOARD[selectedField][1], 8, LIGHT_GREEN);
}

bool all_out(int playerPositions[], int playerNumberStart, int hm_pos){
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        if(playerPositions[i] >= hm_pos){
            return false;
        }
    }
    return true;
}

bool is_someone_on_startpoint(int playerPositions[], int playerNumberStart, int startPoint){
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        if(playerPositions[i] == startPoint){
            return true;
        }
    }
    return false;
}

bool is_player_movable(int playerPositions[], int piece_color, int selectedPlayer, int n){
    int hm_pos, playerNumberStart, startPoint;
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
        hm_pos = BOARD_DATA.YELLOW.hm_pos;
        playerNumberStart = BOARD_DATA.YELLOW.playerNumberStart;
        startPoint = BOARD_DATA.YELLOW.startPoint;
    }
    else{
        hm_pos = BOARD_DATA.GREEN.hm_pos;
        playerNumberStart = BOARD_DATA.GREEN.playerNumberStart;
        startPoint = BOARD_DATA.GREEN.startPoint;
    }
    int occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[playerNumberStart + selectedPlayer], n), playerPositions);
    if(get_color(occupyingPlayer) == piece_color){
        return false;
    }
    else if(n == 6 && !all_out(playerPositions, playerNumberStart, hm_pos) && !is_someone_on_startpoint(playerPositions, playerNumberStart, startPoint)){//need to move out of house
        if(playerPositions[playerNumberStart + selectedPlayer] >= hm_pos){
            return true;
        }
        return false;
    }
    else if(!all_out(playerPositions, playerNumberStart, hm_pos) && playerPositions[playerNumberStart + selectedPlayer] == startPoint){//need to move from startpoint --> this player
        return true;
    }
    else if(!all_out(playerPositions, playerNumberStart, hm_pos) && is_someone_on_startpoint(playerPositions, playerNumberStart, startPoint) && get_color(occupied_by(move_n_fields(piece_color, startPoint, n), playerPositions)) != piece_color){//need to move from startpoint --> not this player
        return false;
    }
    else if(get_color(occupyingPlayer) != piece_color){//if move is even possible
        return true;
    }
    return false;
}

int *move_player(int playerPositions[], int piece_color, int selectedPlayer, int n){
    int player = (piece_color - 2) * BOARD_DATA.h_size + selectedPlayer;
    int occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[player], n), playerPositions);

    playerPositions[16] = playerPositions[player];
    if(occupyingPlayer != -1){//if someone to throw out
        playerPositions = throw_out(playerPositions, piece_color, player, playerPositions[player], n);//throw out player
        return playerPositions;
    }else{
        playerPositions[player] = move_n_fields(piece_color, playerPositions[player], n);//move player to empty field
        return playerPositions;
    }
}

int *move_enemy(int playerPositions[], int piece_color, int n){
    int hm_pos, playerNumberStart, occupyingPlayer, startPoint, movable;
    movable = -1;
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
        hm_pos = BOARD_DATA.YELLOW.hm_pos;
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
                playerPositions[16] = playerPositions[i];//store the old position of the player in playerPositions[16]
                if(occupyingPlayer != -1){
                    playerPositions = throw_out(playerPositions, piece_color, i, playerPositions[i], n);//move player out of home if you have to + throw out player
                    return playerPositions;
                }else{
                    playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player out of home if you have to 
                    return playerPositions;
                }
            }
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] == startPoint && (occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color) && !all_out(playerPositions, playerNumberStart, hm_pos)){
            playerPositions[16] = playerPositions[i];
            playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player from start point if you have to
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] <= BOARD_DATA.end_of_board && move_n_fields(piece_color, playerPositions[i], n) > BOARD_DATA.end_of_board && occupyingPlayer == -1){
            playerPositions[16] = playerPositions[i];
            playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//priorize entering the house
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer != -1 && get_color(occupyingPlayer) != piece_color && rand() % 10 != 0){
            playerPositions[16] = playerPositions[i];
            playerPositions = throw_out(playerPositions, piece_color, i, playerPositions[i], n);//throw out player
            return playerPositions;
        }
    }
    
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA.h_size; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer == -1 && move_n_fields(piece_color, playerPositions[i], n) != playerPositions[i]){
            movable = i;
            if(rand() % 4 != 0){
                playerPositions[16] = playerPositions[i];
                playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player to empty field
                return playerPositions;
            }   
        }
    }
    if(movable != -1){//move a movable player, if not done before
        playerPositions[16] = playerPositions[movable];
        playerPositions[movable] = move_n_fields(piece_color, playerPositions[movable], n);//move player to empty field
    }
    return playerPositions;
}

bool check_for_win(int playerPositions[]){
    for(int i = 0; i < BOARD_DATA.h_size; i++){
        if((playerPositions[i * BOARD_DATA.h_size] >= BOARD_DATA.BLUE.h_start && playerPositions[i * BOARD_DATA.h_size] < BOARD_DATA.BLUE.hm_pos) 
        && (playerPositions[i * BOARD_DATA.h_size + 1] >= BOARD_DATA.BLUE.h_start && playerPositions[i * BOARD_DATA.h_size + 1] < BOARD_DATA.BLUE.hm_pos) 
        && (playerPositions[i * BOARD_DATA.h_size + 2] >= BOARD_DATA.BLUE.h_start && playerPositions[i * BOARD_DATA.h_size + 2] < BOARD_DATA.BLUE.hm_pos) 
        && (playerPositions[i * BOARD_DATA.h_size + 3] >= BOARD_DATA.BLUE.h_start && playerPositions[i * BOARD_DATA.h_size + 3] < BOARD_DATA.BLUE.hm_pos)){
            return true;
        }
    }
    return false;
}

int main(){
    int playerPositions[17] = {56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 27};
    int toClear = 0;
    int r = 0;
    int again = 0;
    int playerTypes[4] = {0, 0, 0, 0};
    int selectedPlayer = 0;
    int oldSelection = 0;
    kb_key_t prevkey1 = kb_Data[1];
    kb_key_t prevkey7 = kb_Data[7];
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
    while(kb_Data[6] != kb_Clear && !check_for_win(playerPositions)){
        for(int i = 2; i < 6 && kb_Data[6] != kb_Clear && !check_for_win(playerPositions); i++){
            again = 1;
            if(playerTypes[i - 2] == 0){//if it's a real player's turn
                r = 0;
                draw(playerPositions, toClear, i, r);
                for(int k = 0; k < again && kb_Data[6] != kb_Clear && !check_for_win(playerPositions); k++){
                    while(kb_Data[6] != kb_Clear){//wait for 2nd to roll the die
                        if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//roll the die
                            r = rand() % 6 + 1;
                            break;
                        }
                        prevkey1 = kb_Data[1];
                        prevkey7 = kb_Data[7];
                        kb_Scan();
                    }
                    draw(playerPositions, toClear, i, r);
                    prevkey1 = kb_Data[1];
                    prevkey7 = kb_Data[7];
                    kb_Scan();
                    for(int j = 0; j < BOARD_DATA.h_size; j++){ 
                        if(is_player_movable(playerPositions, i, j, r)){
                            selectedPlayer = j;
                            break;
                        }else{
                            selectedPlayer = -1;
                        }
                    }
                    if(selectedPlayer != -1){
                        while(kb_Data[6] != kb_Clear){//wait for 2nd to move the player
                            // draw selections
                            draw(playerPositions, toClear, i, r);
                            draw_potential_field(move_n_fields(i, playerPositions[(i - 2) * BOARD_DATA.h_size + selectedPlayer], r), move_n_fields(i, playerPositions[(i - 2) * BOARD_DATA.h_size + oldSelection], r));
                            draw_player_selection(playerPositions, (i - 2) * BOARD_DATA.h_size + selectedPlayer, (i - 2) * BOARD_DATA.h_size + oldSelection);
                            
                            if(kb_Data[1] == kb_2nd && kb_Data[1] != prevkey1){//move the player
                                *playerPositions = *move_player(playerPositions, i, selectedPlayer, r);
                                toClear = playerPositions[16];
                                redraw_field(playerPositions[(i - 2) * BOARD_DATA.h_size + selectedPlayer]);
                                gfx_SwapDraw();
                                redraw_field(playerPositions[(i - 2) * BOARD_DATA.h_size + selectedPlayer]);
                                draw(playerPositions, toClear, i, r);
                                break;
                            }
                            
                            if(kb_Data[7] == kb_Left && kb_Data[7] != prevkey7){
                                oldSelection = selectedPlayer;
                                for(int j = 0; j < BOARD_DATA.h_size; j++){ 
                                    if(selectedPlayer > 0){
                                        selectedPlayer--;
                                    }
                                    else{
                                        selectedPlayer = BOARD_DATA.h_size - 1;
                                    }
                                    if(is_player_movable(playerPositions, i, selectedPlayer, r)){
                                        break;
                                    }
                                }
                            }
                            
                            if(kb_Data[7] == kb_Right && kb_Data[7] != prevkey7){
                                oldSelection = selectedPlayer;
                                for(int j = 0; j < BOARD_DATA.h_size; j++){ 
                                    if(selectedPlayer < BOARD_DATA.h_size - 1){
                                        selectedPlayer++;
                                    }
                                    else{
                                        selectedPlayer = 0;
                                    }
                                    if(is_player_movable(playerPositions, i, selectedPlayer, r)){
                                        break;
                                    }
                                }
                            }
                            prevkey1 = kb_Data[1];
                            prevkey7 = kb_Data[7];
                            kb_Scan();
                        }
                        prevkey1 = kb_Data[1];
                        prevkey7 = kb_Data[7];
                        kb_Scan();
                    }
                    if(check_for_order(playerPositions, i) && again < 3){
                        again++;
                    }   
                }
                msleep(500);
            }
            else{
                for(int k = 0; k < again && kb_Data[6] != kb_Clear && !check_for_win(playerPositions); k++){
                    r = rand() % 6 + 1;
                    *playerPositions = *move_enemy(playerPositions, i, r);
                    toClear = playerPositions[16];
                    draw(playerPositions, toClear, i, r);
                    
                    msleep(500);

                    prevkey1 = kb_Data[1];
                    prevkey7 = kb_Data[7];
                    kb_Scan();

                    if(check_for_order(playerPositions, i) && again < 3){
                        again++;
                    }  
                }
            }
            if(r == 6){i--;}
        }
    }
    gfx_End();
    
}