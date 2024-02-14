#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Board{
    
    public:
        static const int SIZE_CHESS = 8;
        static const int NUM_PIECES = 6;
        Board();
        Board(int chessboard[SIZE_CHESS][SIZE_CHESS],
        int black_captured[NUM_PIECES],
        int white_captured[NUM_PIECES],
        int white_player_points,
        int black_player_points, bool in_checkmate);
        Board(int chessboard[SIZE_CHESS][SIZE_CHESS]);
        ~Board();

        /* first checks if a move is possible
        if the move is possible updates the board */
        bool make_move(int start_row, int start_col, int end_row, int end_col);
        
        //FOR TESTING, MAKES MOVE IGNOEING EVERY RULE
        bool make_move_ir(int start_row, int start_col, int end_row, int end_col);

        /* gets the total points white player has*/
        const int get_white_player_points() const;

        /* gets the total points black player has*/
        const int get_black_player_points() const;

        /* update the total points white player has*/
        void update_white_player_points(int piece);

        /* update the total points black player has*/
        void update_black_player_points(int piece);

        /* gets the vector containing the pieces
        black has lost*/
        const int *get_black_captured() const;

         /* gets the vector containing the pieces
        white has lost*/
        const int *get_white_captured() const;

        /* updates the points in the black_lost
        array based on which piece was taken*/
        void update_black_captured(int piece);
          
        /* updates the points in the white_lost
        array based on which piece was taken*/
        void update_white_captured(int piece);

        /* updates in_checkmate variable with 
        bool in answer*/
        void update_checkmate(bool anwser);

        /* returns the variable in in_checkmate*/
        const bool get_in_checkmate() const;

        /* gets the value in the board at [row][col]*/
        const int get_value_at_position(int row, int col) const;

    private:
        int chessboard[SIZE_CHESS][SIZE_CHESS];
        int black_captured[NUM_PIECES];
        int white_captured[NUM_PIECES];
        int white_player_points;
        int black_player_points;
        //add rules instance.
        bool in_checkmate;






};
#endif