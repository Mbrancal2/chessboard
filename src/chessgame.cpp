#include <iostream>
#include "interface.h"
#include "board.h"
#include "rules.h"
using namespace std;



//below this point are only tests. will make more official in future versions with Catch2
/*int board[8][8] = {{-5,-2,-3,-6,-9,-3,-2,-5},
                       {-1,-1,-1,-1,-1,-1,-1,-1},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {1, 1, 1, 1, 1, 1, 1, 1},
                       {5, 2, 3, 6, 9, 3, 2, 5}};*/
//for testing the rook and if its moveset aligns with real chess moveset.
void test_1_rook_rules(){
    int board[8][8] = {{-5,0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {1, 1, 1, 1, 1, 1, 1, 1},
                       {5, 2, 3, 6, 9, 3, 2, 5}};
    //Interface interface1(board);
    //see if rook can move out of bounds:
    //interface1.make_move(0,0,-1,0);
    //interface1.make_move(0,0,0,-1);
    //interface1.make_move(0,0,-1,-1);
    //interface1.make_move(0,0,8,0);
    //interface1.make_move(0,0,0,8);
    //interface1.make_move(0,0,8,8);
    
    
    
}
int main(){
    //Interface game;
    test_1_rook_rules();
    //Board b1_test()
    //game.print_board_state();
    //game.make_move();
    //game.print_board_state();
    return 0;

    //TODO TESTS: TEST MOVE, TEST RULES- MOVE OUT OF BOUNDS, MOVE PAWN, MOVE ROOK, MOVE KNIGHT, MOVE BISHOP, MOVE KING, MOVE QUEEN. TEST LOST TABLE. TEST WIN CONDITION.
}
