const int LEFT_MARGIN = 44;
const int TOP_MARGIN = 5;

const int BOARD[72][3] = {{LEFT_MARGIN + 126, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 126, TOP_MARGIN + 21, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 42, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 63, WHITE}, {LEFT_MARGIN + 126, TOP_MARGIN + 84, WHITE},
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
                        {LEFT_MARGIN + 105, TOP_MARGIN, WHITE},

                        {LEFT_MARGIN + 105, TOP_MARGIN + 21, BLUE}, {LEFT_MARGIN + 105, TOP_MARGIN + 42, BLUE},  {LEFT_MARGIN + 105, TOP_MARGIN + 63, BLUE}, {LEFT_MARGIN + 105, TOP_MARGIN + 84, BLUE},
                        {LEFT_MARGIN + 189, TOP_MARGIN + 105, RED}, {LEFT_MARGIN + 168, TOP_MARGIN + 105, RED}, {LEFT_MARGIN + 147, TOP_MARGIN + 105, RED}, {LEFT_MARGIN + 126, TOP_MARGIN + 105, RED},
                        {LEFT_MARGIN + 105, TOP_MARGIN + 189, YELLOW}, {LEFT_MARGIN + 105, TOP_MARGIN + 168, YELLOW}, {LEFT_MARGIN + 105, TOP_MARGIN + 147, YELLOW}, {LEFT_MARGIN + 105, TOP_MARGIN + 126, YELLOW},
                        {LEFT_MARGIN + 21, TOP_MARGIN + 105, GREEN}, {LEFT_MARGIN + 42, TOP_MARGIN + 105, GREEN}, {LEFT_MARGIN + 63, TOP_MARGIN + 105, GREEN}, {LEFT_MARGIN + 84, TOP_MARGIN + 105, GREEN},

                        {LEFT_MARGIN + 189, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 210, TOP_MARGIN, BLUE}, {LEFT_MARGIN + 189, TOP_MARGIN + 21, BLUE}, {LEFT_MARGIN + 210, TOP_MARGIN + 21, BLUE},
                        {LEFT_MARGIN + 189, TOP_MARGIN + 189, RED}, {LEFT_MARGIN + 210, TOP_MARGIN + 189, RED}, {LEFT_MARGIN + 189, TOP_MARGIN + 210, RED}, {LEFT_MARGIN + 210, TOP_MARGIN + 210, RED},
                        {LEFT_MARGIN, TOP_MARGIN + 189, YELLOW}, {LEFT_MARGIN + 21, TOP_MARGIN + 189, YELLOW}, {LEFT_MARGIN, TOP_MARGIN + 210, YELLOW}, {LEFT_MARGIN + 21, TOP_MARGIN + 210, YELLOW},
                        {LEFT_MARGIN, TOP_MARGIN, GREEN}, {LEFT_MARGIN + 21, TOP_MARGIN, GREEN}, {LEFT_MARGIN, TOP_MARGIN + 21, GREEN}, {LEFT_MARGIN + 21, TOP_MARGIN + 21, GREEN}
                        };

const struct{
    struct{
        int h_offset = 39;
        int h_start = 40;
        int startPoint = 0;
        int hm_pos = 56;
        int playerNumberStart = 0;
    } BLUE;

    struct {
        int h_offset = 9;
        int h_start = 44;
        int startPoint = 10;
        int hm_pos = 60;
        int playerNumberStart = 4;
    } RED;

    struct{
        int h_offset = 19;
        int h_start = 48;
        int startPoint = 20;
        int hm_pos = 64;
        int playerNumberStart = 8;
    } YELLOW;

    struct{
        int h_offset = 29;
        int h_start = 52;
        int startPoint = 30;
        int hm_pos = 68;
        int playerNumberStart = 12;
    } GREEN;
    
    int player_count = 16;
    int end_of_board = 39;
    int end_of_home = 15;
    int h_size = 4;
} BOARD_DATA;