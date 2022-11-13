#include "graphx.h"
#include "gfx/colors.h"
#include "const.h"
#include "draw.hpp"
#include "keypadc.h"
#include <tice.h>

int get_color(int playerNumber){
    if(playerNumber >= 0 && playerNumber < BOARD_DATA[0]){
        return playerNumber / BOARD_DATA[2] + 2;
    }
    else{
        return -1;
    }
}

int occupied_by(int position, int playerPositions[]){
    for(int i = 0; i < BOARD_DATA[0]; i++){
        if(playerPositions[i] == position){
            return i;
        }
    }
    return -1;
}

int move_n_fields(int piece_color, int position, int n){
    int h_offset, h_start, startPoint;

    startPoint = BOARD_COLOR_DATA[piece_color - 2][2];
    h_offset = BOARD_COLOR_DATA[piece_color - 2][0];
    h_start = BOARD_COLOR_DATA[piece_color - 2][1];

    if(position > BOARD_DATA[1] + BOARD_DATA[0] && n == 6){//move out of home
        return startPoint;
    }
    else if(position <= h_offset && position + n > h_offset && position + n <= h_offset + BOARD_DATA[2]){//move into house
        return h_start + (position + n - (h_offset + 1));
    }
    else if(position <= h_offset && position + n > h_offset){//dont move if you cant move any further
        return position;
    }

    else if((position >= h_start && position + n < h_start + BOARD_DATA[2])){//move inside house
        return position + n;
    }
    else if(position + n <= BOARD_DATA[1]){//move normally
        return position + n;
    }
    else if(position <= BOARD_DATA[1]){//go from end of board to 0
        return position + n - (BOARD_DATA[1] + 1);
    }
    else{
        return position;
    }
}

int *throw_out(int playerPositions[], int player, int old_position, int n){
    int new_position = move_n_fields(get_color(player), old_position, n);
    int occupyingPlayer = occupied_by(new_position, playerPositions);
    
    playerPositions[occupyingPlayer] = BOARD_DATA[1] + BOARD_DATA[0] + 1 + occupyingPlayer;
    playerPositions[player] = new_position;
    return playerPositions;
}

int check_for_order(int playerPositions[], int piece_color){
    int h_start, playerNumberStart;
    bool houseFieldIsOccupied = true;
    int fields = 0;
    h_start = BOARD_COLOR_DATA[piece_color - 2][1];
    playerNumberStart = BOARD_COLOR_DATA[piece_color - 2][4];

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
        if(playerPositions[i] < h_start){//if player on the field
            return false;
        }
        else if(playerPositions[i] > BOARD_DATA[1]){//one more player in home
            fields++;
        }
    }
    if(fields == BOARD_DATA[2]){//if all players in home
        return true;
    }
    else{
        fields = 0;//otherwise reset fields
    }

    for(int j = 1; j < BOARD_DATA[2]; j++){
        for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
            if(playerPositions[i] == h_start + BOARD_DATA[2] - j){
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

bool all_out(int playerPositions[], int playerNumberStart, int hm_pos){
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
        if(playerPositions[i] >= hm_pos){
            return false;
        }
    }
    return true;
}

bool is_player_movable(int playerPositions[], int piece_color, int selectedPlayer, int n){
    int hm_pos, playerNumberStart, startPoint;
    
    hm_pos = BOARD_COLOR_DATA[piece_color - 2][3];
    playerNumberStart = BOARD_COLOR_DATA[piece_color - 2][4];
    startPoint = BOARD_COLOR_DATA[piece_color - 2][2];

    int occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[playerNumberStart + selectedPlayer], n), playerPositions);
    if(get_color(occupyingPlayer) == piece_color){
        return false;
    }
    else if(n == 6 && !all_out(playerPositions, playerNumberStart, hm_pos) && piece_color != get_color(occupyingPlayer)){;//need to move out of house
        if(playerPositions[playerNumberStart + selectedPlayer] >= hm_pos){
            return true;
        }
        return false;
    }
    else if(!all_out(playerPositions, playerNumberStart, hm_pos) && playerPositions[playerNumberStart + selectedPlayer] == startPoint){//need to move from startpoint --> this player
        return true;
    }
    else if(!all_out(playerPositions, playerNumberStart, hm_pos) && piece_color == get_color(occupyingPlayer) && get_color(occupied_by(move_n_fields(piece_color, startPoint, n), playerPositions)) != piece_color){//need to move from startpoint --> not this player
        return false;
    }
    else if(get_color(occupyingPlayer) != piece_color){//if move is even possible
        return true;
    }
    return false;
}

int *move_player(int playerPositions[], int piece_color, int selectedPlayer, int n){
    int player = (piece_color - 2) * BOARD_DATA[2] + selectedPlayer;
    int occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[player], n), playerPositions);

    playerPositions[BOARD_DATA[0]] = playerPositions[player];
    if(occupyingPlayer != -1){//if someone to throw out
        playerPositions = throw_out(playerPositions, player, playerPositions[player], n);//throw out player
        return playerPositions;
    }else{
        playerPositions[player] = move_n_fields(piece_color, playerPositions[player], n);//move player to empty field
        return playerPositions;
    }
}

int *move_enemy(int playerPositions[], int piece_color, int n){
    int hm_pos, playerNumberStart, occupyingPlayer, startPoint, movable;
    movable = -1;
    
    hm_pos = BOARD_COLOR_DATA[piece_color - 2][3];
    playerNumberStart = BOARD_COLOR_DATA[piece_color - 2][4];
    startPoint = BOARD_COLOR_DATA[piece_color - 2][2];

    occupyingPlayer = occupied_by(startPoint, playerPositions);
    if(occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color){
        for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
            if(n == 6 && playerPositions[i] >= hm_pos){
                playerPositions[BOARD_DATA[0]] = playerPositions[i];//store the old position of the player in the last value of playerPositions[]
                if(occupyingPlayer != -1){
                    playerPositions = throw_out(playerPositions, i, playerPositions[i], n);//move player out of home if you have to + throw out player
                    return playerPositions;
                }else{
                    playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player out of home if you have to 
                    return playerPositions;
                }
            }
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] == startPoint && (occupyingPlayer == -1 || get_color(occupyingPlayer) != piece_color) && !all_out(playerPositions, playerNumberStart, hm_pos)){
            playerPositions[BOARD_DATA[0]] = playerPositions[i];
            playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player from start point if you have to
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] <= BOARD_DATA[1] && move_n_fields(piece_color, playerPositions[i], n) > BOARD_DATA[1] && occupyingPlayer == -1){
            playerPositions[BOARD_DATA[0]] = playerPositions[i];
            playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//priorize entering the house
            return playerPositions;
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer != -1 && get_color(occupyingPlayer) != piece_color && rand() % 10 != 0){
            playerPositions[BOARD_DATA[0]] = playerPositions[i];
            playerPositions = throw_out(playerPositions, i, playerPositions[i], n);//throw out player
            return playerPositions;
        }
    }
    
    for(int i = playerNumberStart; i < playerNumberStart + BOARD_DATA[2]; i++){
        occupyingPlayer = occupied_by(move_n_fields(piece_color, playerPositions[i], n), playerPositions);
        if(playerPositions[i] < hm_pos && occupyingPlayer == -1 && move_n_fields(piece_color, playerPositions[i], n) != playerPositions[i]){
            movable = i;
            if(rand() % 4 != 0){
                playerPositions[BOARD_DATA[0]] = playerPositions[i];
                playerPositions[i] = move_n_fields(piece_color, playerPositions[i], n);//move player to empty field
                return playerPositions;
            }   
        }
    }
    if(movable != -1){//move a movable player, if not done before
        playerPositions[BOARD_DATA[0]] = playerPositions[movable];
        playerPositions[movable] = move_n_fields(piece_color, playerPositions[movable], n);//move player to empty field
    }
    return playerPositions;
}

int check_for_win(int playerPositions[]){
    for(int i = 0; i < BOARD_DATA[4]; i++){
        for(int j = 0; j < BOARD_DATA[2]; j++){
            if(!(playerPositions[i * BOARD_DATA[2] + j] > BOARD_DATA[1] && playerPositions[i * BOARD_DATA[2] + j] <= BOARD_DATA[1] + BOARD_DATA[0])){
                break;
            }
            if(j == BOARD_DATA[2] - 1){
                return j + 2;
            }
        }
    }
    return 0;
}