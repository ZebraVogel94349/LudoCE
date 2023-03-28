#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include "gfx/colors.h"
#include "const.h"
#include "draw.hpp"

int get_color(int playerNumber, int boardType){
    if(playerNumber >= 0 && playerNumber < BOARD_DATA[boardType][0]){
        return playerNumber / BOARD_DATA[boardType][2] + 2;
    }
    return -1;
}

int occupied_by(int position, int playerPositions[], int boardType){
    for(int i = 0; i < BOARD_DATA[boardType][0]; i++){
        if(playerPositions[i] == position){
            return i;
        }
    }
    return -1;
}

int move_n_fields(int pieceColor, int position, int n, int boardType){
    int h_offset, h_start, startPoint;

    startPoint = BOARD_COLOR_DATA[boardType][pieceColor - 2][2];
    h_offset = BOARD_COLOR_DATA[boardType][pieceColor - 2][0];
    h_start = BOARD_COLOR_DATA[boardType][pieceColor - 2][1];

    if(position > BOARD_DATA[boardType][1] + BOARD_DATA[boardType][0] && n == 6){//move out of home
        return startPoint;
    }
    else if(position <= h_offset && position + n > h_offset && position + n <= h_offset + BOARD_DATA[boardType][2]){//move into house
        return h_start + (position + n - (h_offset + 1));
    }
    else if(position <= h_offset && position + n > h_offset){//dont move if you cant move any further
        return position;
    }

    else if((position >= h_start && position + n < h_start + BOARD_DATA[boardType][2])){//move inside house
        return position + n;
    }
    else if(position <= BOARD_DATA[boardType][1]){//move normally
        return (position + n) % (BOARD_DATA[boardType][1] + 1);
    }
    return position;
}

int *throw_out(int playerPositions[], int player, int oldPosition, int n, int boardType){
    int new_position = move_n_fields(get_color(player, boardType), oldPosition, n, boardType);
    int occupyingPlayer = occupied_by(new_position, playerPositions, boardType);
    
    playerPositions[occupyingPlayer] = BOARD_DATA[boardType][1] + BOARD_DATA[boardType][0] + 1 + occupyingPlayer;
    playerPositions[player] = new_position;
    return playerPositions;
}

int check_for_order(int playerPositions[], int pieceColor, int figureCount, int boardType){
    int h_start, playerNumberStart;
    bool houseFieldIsOccupied = true;
    int fields = 0;
    h_start = BOARD_COLOR_DATA[boardType][pieceColor - 2][1];
    playerNumberStart = BOARD_COLOR_DATA[boardType][pieceColor - 2][4];

    for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
        if(playerPositions[i] < h_start && playerPositions[i] > -1){//if player on the field
            return false;
        }
        else if(playerPositions[i] > BOARD_DATA[boardType][1]){//one more player in home
            fields++;
        }
    }
    if(fields == figureCount){//if all players in home
        return true;
    }

    fields = 0;

    for(int j = 1; j < figureCount; j++){
        for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
            if(playerPositions[i] == h_start + BOARD_DATA[boardType][2] - j){
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

bool all_out(int playerPositions[], int playerNumberStart, int hm_pos, int figureCount){
    for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
        if(playerPositions[i] >= hm_pos){
            return false;
        }
    }
    return true;
}

bool is_player_movable(int playerPositions[], int pieceColor, int selectedPlayer, int n, int figureCount, int boardType){
    int hm_pos, playerNumberStart, startPoint;
    
    hm_pos = BOARD_COLOR_DATA[boardType][pieceColor - 2][3];
    playerNumberStart = BOARD_COLOR_DATA[boardType][pieceColor - 2][4];
    startPoint = BOARD_COLOR_DATA[boardType][pieceColor - 2][2];

    int occupyingPlayer = occupied_by(move_n_fields(pieceColor, playerPositions[playerNumberStart + selectedPlayer], n, boardType), playerPositions, boardType);
    if(get_color(occupyingPlayer, boardType) == pieceColor){
        return false;
    }
    else if(!all_out(playerPositions, playerNumberStart, hm_pos, figureCount) && playerPositions[playerNumberStart + selectedPlayer] == startPoint){//player needs to move from start point
        return true;
    }
    else if(n == 6 && !all_out(playerPositions, playerNumberStart, hm_pos, figureCount) && pieceColor != get_color(occupyingPlayer, boardType)){;//need to move out of house
        if(playerPositions[playerNumberStart + selectedPlayer] >= hm_pos){
            return true;
        }
        return false;
    }
    for(int i = 0; i < figureCount; i++){
        if(i != selectedPlayer && !all_out(playerPositions, playerNumberStart, hm_pos, figureCount) && playerPositions[playerNumberStart + i] == startPoint && get_color(occupied_by(move_n_fields(pieceColor, playerPositions[playerNumberStart + i], n, boardType), playerPositions, boardType), boardType) != pieceColor){
            return false;
        }
    }
    return true;
}

int *move_player(int playerPositions[], int pieceColor, int selectedPlayer, int n, int boardType){
    int player = (pieceColor - 2) * BOARD_DATA[boardType][2] + selectedPlayer;
    int occupyingPlayer = occupied_by(move_n_fields(pieceColor, playerPositions[player], n, boardType), playerPositions, boardType);

    playerPositions[BOARD_DATA[boardType][0]] = playerPositions[player];
    if(occupyingPlayer != -1){//if someone to throw out
        playerPositions = throw_out(playerPositions, player, playerPositions[player], n, boardType);//throw out player
    }
    else{
        playerPositions[player] = move_n_fields(pieceColor, playerPositions[player], n, boardType);//move player to empty field
    }
    return playerPositions;
}

int *move_enemy(int playerPositions[], int pieceColor, int n, int botStrength, int figureCount, int boardType){
    int occupyingPlayer, movableCounter, throwoutCounter, playerNumberStart;
    bool playersMovable[4] = {false, false, false, false};
    bool throwoutPossible[4] = {false, false, false, false};
    movableCounter = 0;
    throwoutCounter = 0;
    playerNumberStart = BOARD_COLOR_DATA[boardType][pieceColor - 2][4];

    for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
        if(is_player_movable(playerPositions, pieceColor, i - playerNumberStart, n, figureCount, boardType)){
            playersMovable[i - playerNumberStart] = true;
            movableCounter++;
        }
        occupyingPlayer = occupied_by(move_n_fields(pieceColor, playerPositions[i], n, boardType), playerPositions, boardType);
        if(occupyingPlayer != -1 && get_color(occupyingPlayer, boardType) != pieceColor && playersMovable[i - playerNumberStart]){
            throwoutPossible[i - playerNumberStart] = true;
            throwoutCounter++;
        }
    }

    if(throwoutCounter > 0){
        for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
            if(throwoutPossible[i - playerNumberStart] && rand() % (3 * (botStrength + 1)) != 0){
                playerPositions[BOARD_DATA[boardType][0]] = playerPositions[i];
                playerPositions = throw_out(playerPositions, i, playerPositions[i], n, boardType);
                return playerPositions;
            }
        }
    }
    else if(movableCounter > 0){
        for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
            if(playersMovable[i - playerNumberStart] && rand() % (botStrength + 2) != 0){
                playerPositions[BOARD_DATA[boardType][0]] = playerPositions[i];
                playerPositions[i] = move_n_fields(pieceColor, playerPositions[i], n, boardType);
                return playerPositions;
            }  
        }
    }

    for(int i = playerNumberStart; i < playerNumberStart + figureCount; i++){
        if(playersMovable[i - playerNumberStart]){
            playerPositions[BOARD_DATA[boardType][0]] = playerPositions[i];
            if(throwoutPossible[i - playerNumberStart]){
                playerPositions = throw_out(playerPositions, i, playerPositions[i], n, boardType);
            }
            else{
                playerPositions[i] = move_n_fields(pieceColor, playerPositions[i], n, boardType);
            }
            return playerPositions;
        }
    }
    return playerPositions;
}

int check_for_win(int playerPositions[], int figureCount, int boardType){
    for(int i = 0; i < BOARD_DATA[boardType][0] / BOARD_DATA[boardType][2]; i++){
        for(int j = 0; j < figureCount; j++){
            if(!(playerPositions[i * BOARD_DATA[boardType][2] + j] > BOARD_DATA[boardType][1] && playerPositions[i * BOARD_DATA[boardType][2] + j] <= BOARD_DATA[boardType][1] + BOARD_DATA[boardType][0])){
                break;
            }
            if(j == figureCount - 1){
                return i + 2;
            }
        }
    }
    return 0;
}