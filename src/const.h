#ifndef CONST_H
#define CONST_H

const int VERSION = 2;

const int LEFT_MARGIN = 46;
const int TOP_MARGIN = 4;

const int BOARD[2][96][3] = { //4-board
                            {{LEFT_MARGIN + 126, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 126, TOP_MARGIN + 21, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 42, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 63, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 84, WHITE},
                            {LEFT_MARGIN + 147, TOP_MARGIN + 84, WHITE}, {LEFT_MARGIN + 168, TOP_MARGIN + 84, WHITE}, {LEFT_MARGIN + 189, TOP_MARGIN + 84, WHITE}, {LEFT_MARGIN + 210, TOP_MARGIN + 84, WHITE},
                            {LEFT_MARGIN + 210, TOP_MARGIN + 105, WHITE}, {LEFT_MARGIN + 210, TOP_MARGIN + 126, RED},
                            {LEFT_MARGIN + 189, TOP_MARGIN + 126, WHITE}, {LEFT_MARGIN + 168, TOP_MARGIN + 126, WHITE} , {LEFT_MARGIN + 147, TOP_MARGIN + 126, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 126, WHITE},
                            {LEFT_MARGIN + 126, TOP_MARGIN + 147, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 168, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 189, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 210, WHITE},
                            {LEFT_MARGIN + 105, TOP_MARGIN + 210, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 210, YELLOW},
                            {LEFT_MARGIN + 84, TOP_MARGIN + 189, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 168, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 147, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 126, WHITE},
                            {LEFT_MARGIN + 63, TOP_MARGIN + 126, WHITE}, {LEFT_MARGIN + 42, TOP_MARGIN + 126, WHITE}, {LEFT_MARGIN + 21, TOP_MARGIN + 126, WHITE}, {LEFT_MARGIN, TOP_MARGIN + 126, WHITE},
                            {LEFT_MARGIN, TOP_MARGIN + 105, WHITE}, {LEFT_MARGIN, TOP_MARGIN + 84, GREEN},
                            {LEFT_MARGIN + 21, TOP_MARGIN + 84, WHITE}, {LEFT_MARGIN + 42, TOP_MARGIN + 84, WHITE}, {LEFT_MARGIN + 63, TOP_MARGIN + 84, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 84, WHITE},
                            {LEFT_MARGIN + 84, TOP_MARGIN + 63, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 42, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN + 21, WHITE}, {LEFT_MARGIN + 84, TOP_MARGIN, WHITE},
                            {LEFT_MARGIN + 105, TOP_MARGIN, WHITE}, //40
                            //home
                            {LEFT_MARGIN + 105, TOP_MARGIN + 21, BLUE}, {LEFT_MARGIN + 105, TOP_MARGIN + 42, BLUE},  {LEFT_MARGIN + 105, TOP_MARGIN + 63, BLUE}, {LEFT_MARGIN + 105, TOP_MARGIN + 84, BLUE},
                            {LEFT_MARGIN + 189, TOP_MARGIN + 105, RED}, {LEFT_MARGIN + 168, TOP_MARGIN + 105, RED}, {LEFT_MARGIN + 147, TOP_MARGIN + 105, RED}, {LEFT_MARGIN + 126, TOP_MARGIN + 105, RED},
                            {LEFT_MARGIN + 105, TOP_MARGIN + 189, YELLOW}, {LEFT_MARGIN + 105, TOP_MARGIN + 168, YELLOW}, {LEFT_MARGIN + 105, TOP_MARGIN + 147, YELLOW}, {LEFT_MARGIN + 105, TOP_MARGIN + 126, YELLOW},
                            {LEFT_MARGIN + 21, TOP_MARGIN + 105, GREEN}, {LEFT_MARGIN + 42, TOP_MARGIN + 105, GREEN}, {LEFT_MARGIN + 63, TOP_MARGIN + 105, GREEN}, {LEFT_MARGIN + 84, TOP_MARGIN + 105, GREEN},
                            //house
                            {LEFT_MARGIN + 189, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 210, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 189, TOP_MARGIN + 21, BLUE}, {LEFT_MARGIN + 210, TOP_MARGIN + 21, BLUE},
                            {LEFT_MARGIN + 189, TOP_MARGIN + 189, RED}, {LEFT_MARGIN + 210, TOP_MARGIN + 189, RED}, {LEFT_MARGIN + 189, TOP_MARGIN + 210, RED}, {LEFT_MARGIN + 210, TOP_MARGIN + 210, RED},
                            {LEFT_MARGIN, TOP_MARGIN + 189, YELLOW}, {LEFT_MARGIN + 21, TOP_MARGIN + 189, YELLOW}, {LEFT_MARGIN, TOP_MARGIN + 210, YELLOW}, {LEFT_MARGIN + 21, TOP_MARGIN + 210, YELLOW},
                            {LEFT_MARGIN, TOP_MARGIN, GREEN}, {LEFT_MARGIN + 21, TOP_MARGIN, GREEN}, {LEFT_MARGIN, TOP_MARGIN + 21, GREEN}, {LEFT_MARGIN + 21, TOP_MARGIN + 21, GREEN}
                            }, //6-board
                            {{LEFT_MARGIN + 126, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 126, TOP_MARGIN + 19, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 38, WHITE}, 
                            {LEFT_MARGIN + 142, TOP_MARGIN + 48, WHITE}, {LEFT_MARGIN + 158, TOP_MARGIN + 58, WHITE},
                            {LEFT_MARGIN + 174, TOP_MARGIN + 48, WHITE}, {LEFT_MARGIN + 190, TOP_MARGIN + 38, WHITE}, 
                            {LEFT_MARGIN + 200, TOP_MARGIN + 54, WHITE}, {LEFT_MARGIN + 210, TOP_MARGIN + 70, RED},
                            {LEFT_MARGIN + 194, TOP_MARGIN + 80, WHITE}, {LEFT_MARGIN + 178, TOP_MARGIN + 90, WHITE},
                            {LEFT_MARGIN + 178, TOP_MARGIN + 109, WHITE}, {LEFT_MARGIN + 178, TOP_MARGIN + 128, WHITE} , 
                            {LEFT_MARGIN + 194, TOP_MARGIN + 138, WHITE}, {LEFT_MARGIN + 210, TOP_MARGIN + 148, WHITE},
                            {LEFT_MARGIN + 200, TOP_MARGIN + 164, WHITE}, {LEFT_MARGIN + 190, TOP_MARGIN + 180, YELLOW}, 
                            {LEFT_MARGIN + 174, TOP_MARGIN + 170, WHITE}, {LEFT_MARGIN + 158, TOP_MARGIN + 160, WHITE}, 
                            {LEFT_MARGIN + 142, TOP_MARGIN + 170, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 180, WHITE},
                            {LEFT_MARGIN + 126, TOP_MARGIN + 199, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 218, WHITE}, 
                            {LEFT_MARGIN + 107, TOP_MARGIN + 218, WHITE}, {LEFT_MARGIN + 88, TOP_MARGIN + 218, GREEN},
                            {LEFT_MARGIN + 88, TOP_MARGIN + 199, WHITE}, {LEFT_MARGIN + 88, TOP_MARGIN + 180, WHITE}, 
                            {LEFT_MARGIN + 72, TOP_MARGIN + 170, WHITE}, {LEFT_MARGIN + 56, TOP_MARGIN + 160, WHITE},
                            {LEFT_MARGIN + 40, TOP_MARGIN + 170, WHITE}, {LEFT_MARGIN + 24, TOP_MARGIN + 180, WHITE},
                            {LEFT_MARGIN + 14, TOP_MARGIN + 164, WHITE}, {LEFT_MARGIN + 4, TOP_MARGIN + 148, PURPLE},
                            {LEFT_MARGIN + 20, TOP_MARGIN + 138, WHITE}, {LEFT_MARGIN + 36, TOP_MARGIN + 128, WHITE},
                            {LEFT_MARGIN + 36, TOP_MARGIN + 109, WHITE}, {LEFT_MARGIN + 36, TOP_MARGIN + 90, WHITE}, 
                            {LEFT_MARGIN + 20, TOP_MARGIN + 80, WHITE}, {LEFT_MARGIN + 4, TOP_MARGIN + 70, WHITE},
                            {LEFT_MARGIN + 14, TOP_MARGIN + 54, WHITE}, {LEFT_MARGIN + 24, TOP_MARGIN + 38, CYAN},
                            {LEFT_MARGIN + 40, TOP_MARGIN + 48, WHITE}, {LEFT_MARGIN + 56, TOP_MARGIN + 58, WHITE},
                            {LEFT_MARGIN + 72, TOP_MARGIN + 48, WHITE}, {LEFT_MARGIN + 88, TOP_MARGIN + 38, WHITE},
                            {LEFT_MARGIN + 88, TOP_MARGIN + 19, WHITE}, {LEFT_MARGIN + 88, TOP_MARGIN, WHITE},
                            {LEFT_MARGIN + 107, TOP_MARGIN, WHITE}, //48
                            //home
                            {LEFT_MARGIN + 107, TOP_MARGIN + 19, BLUE}, {LEFT_MARGIN + 107, TOP_MARGIN + 38, BLUE},  {LEFT_MARGIN + 107, TOP_MARGIN + 57, BLUE}, {LEFT_MARGIN + 107, TOP_MARGIN + 76, BLUE},
                            {LEFT_MARGIN + 184, TOP_MARGIN + 64, RED}, {LEFT_MARGIN + 168, TOP_MARGIN + 74, RED}, {LEFT_MARGIN + 152, TOP_MARGIN + 84, RED}, {LEFT_MARGIN + 136, TOP_MARGIN + 94, RED},
                            {LEFT_MARGIN + 184, TOP_MARGIN + 154, YELLOW}, {LEFT_MARGIN + 168, TOP_MARGIN + 144, YELLOW}, {LEFT_MARGIN + 152, TOP_MARGIN + 134, YELLOW}, {LEFT_MARGIN + 136, TOP_MARGIN + 124, YELLOW},
                            {LEFT_MARGIN + 107, TOP_MARGIN + 199, GREEN}, {LEFT_MARGIN + 107, TOP_MARGIN + 180, GREEN}, {LEFT_MARGIN + 107, TOP_MARGIN + 161, GREEN}, {LEFT_MARGIN + 107, TOP_MARGIN + 142, GREEN},
                            {LEFT_MARGIN + 30, TOP_MARGIN + 154, PURPLE}, {LEFT_MARGIN + 46, TOP_MARGIN + 144, PURPLE}, {LEFT_MARGIN + 62, TOP_MARGIN + 134, PURPLE}, {LEFT_MARGIN + 78, TOP_MARGIN + 124, PURPLE},
                            {LEFT_MARGIN + 30, TOP_MARGIN + 64, CYAN}, {LEFT_MARGIN + 46, TOP_MARGIN + 74, CYAN}, {LEFT_MARGIN + 62, TOP_MARGIN + 84, CYAN}, {LEFT_MARGIN + 78, TOP_MARGIN + 94, CYAN},
                            //house
                            {LEFT_MARGIN + 205, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 224, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 205, TOP_MARGIN + 19, BLUE}, {LEFT_MARGIN + 224, TOP_MARGIN + 19, BLUE},
                            {LEFT_MARGIN + 205, TOP_MARGIN + 100, RED}, {LEFT_MARGIN + 224, TOP_MARGIN + 100, RED}, {LEFT_MARGIN + 205, TOP_MARGIN + 119, RED}, {LEFT_MARGIN + 224, TOP_MARGIN + 119, RED},
                            {LEFT_MARGIN + 205, TOP_MARGIN + 199, YELLOW}, {LEFT_MARGIN + 224, TOP_MARGIN + 199, YELLOW}, {LEFT_MARGIN + 205, TOP_MARGIN + 218, YELLOW}, {LEFT_MARGIN + 224, TOP_MARGIN + 218, YELLOW},
                            {LEFT_MARGIN - 10, TOP_MARGIN + 199, GREEN}, {LEFT_MARGIN + 9, TOP_MARGIN + 199, GREEN}, {LEFT_MARGIN - 10, TOP_MARGIN + 218, GREEN}, {LEFT_MARGIN + 9, TOP_MARGIN + 218, GREEN},
                            {LEFT_MARGIN - 10, TOP_MARGIN + 100, PURPLE}, {LEFT_MARGIN + 9, TOP_MARGIN + 100, PURPLE}, {LEFT_MARGIN - 10, TOP_MARGIN + 119, PURPLE}, {LEFT_MARGIN + 9, TOP_MARGIN + 119, PURPLE},
                            {LEFT_MARGIN - 10, TOP_MARGIN, CYAN}, {LEFT_MARGIN + 9, TOP_MARGIN, CYAN}, {LEFT_MARGIN - 10, TOP_MARGIN + 19, CYAN}, {LEFT_MARGIN + 9, TOP_MARGIN + 19, CYAN}
                            }};

const int BOARD_PLAYER_NAMING[2][6][2] = { //4-board
                                         {{LEFT_MARGIN + 210 + 20, TOP_MARGIN}, {LEFT_MARGIN + 210 + 20, TOP_MARGIN + 189}, {LEFT_MARGIN - 30, TOP_MARGIN + 189}, {LEFT_MARGIN - 30, TOP_MARGIN}},
                                           //6-board
                                         {{LEFT_MARGIN + 224 + 18, TOP_MARGIN}, {LEFT_MARGIN + 224 + 18, TOP_MARGIN + 100}, {LEFT_MARGIN + 224 + 18, TOP_MARGIN + 199}, {LEFT_MARGIN - 10 - 22, TOP_MARGIN + 199}, {LEFT_MARGIN - 10 - 22, TOP_MARGIN + 100}, {LEFT_MARGIN - 10 - 22, TOP_MARGIN}}
                                         };

//h_offset, hm_start, startPoint, h_pos and playerNumberStart for each color
const int BOARD_COLOR_DATA[2][6][5] = {
    {{39, 40, 0, 56, 0},//BLUE
    {9, 44, 10, 60, 4},//RED
    {19, 48, 20, 64, 8},//YELLOW
    {29, 52, 30, 68, 12}},//GREEN

    {{47, 48, 0, 72, 0},//BLUE
    {7, 52, 8, 76, 4},//RED
    {15, 56, 16, 80, 8},//YELLOW
    {23, 60, 24, 84, 12},//GREEN
    {31, 64, 32, 88, 16},//PURPLE
    {39, 68, 40, 92, 20}}//CYAN
};

//playerCount, endOfBoard, h_size, boardSize, colorCount, fieldSize
const int BOARD_DATA[2][7] = {{16, 39, 4, 72, 4, 8},   //4-board
                              {24, 47, 4, 96, 4, 7}};  //6-board
#endif