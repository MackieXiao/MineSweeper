// =============================================================================
// File Name    : chessboard.h
// Project      : MineSweeper
// Brief        : Header file of chessboard.c
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#ifndef CHESSBOARD_H
#define CHESSBOARD_H


// =========================================================
// File Include
// =========================================================
#include "iostream"
#include "stdlib.h"
#include "ctime"
#include <unordered_map>
#include <vector>



// =========================================================
// Macro Define
// =========================================================
//block status to describe chessboard info
#define BLK_STA_NOMINE  0
#define BLK_STA_MINE    9

//block mask to describe display content
#define BLK_MASK_CLOSE      0
#define BLK_MASK_OPEN       1
#define BLK_MASK_FLAG       2
#define BLK_MASK_BOOM       3
#define BLK_MASK_WRONGMINE  4
#define BLK_MASK_QUESTION   5

//game status
#define GAME_STA_PENDING    0
#define GAME_STA_PLAYING    1
#define GAME_STA_OVER       2
#define GAME_STA_PASS       3

//mouse command event
#define MOUSE_EVENT_NONE    0
#define MOUSE_EVENT_SELECT  1
#define MOUSE_EVENT_EXPAND  2
#define MOUSE_EVENT_FLAG    3


// =========================================================
// Class Define
// =========================================================
//chessboard class, mainly used to define the basic logic
//variable and method of minesweeper
class ChessBoard {
public:
    ChessBoard(int row, int col, int mine);
    ~ChessBoard();
    int GetRowNumber(void);
    int GetColNumber(void);
    int GetMineNumber(void);
    int GetRunTime(void);
    int GetGameStatus(void);
    int GetFlagNumber(void);
    void UpdateRunTime(void);
    void UpdateChessBoard(int pos_row, int pos_col, int mouse_event, int f_start);
    int **p_chessboard;
    int **p_mask;

private:
    void FisherYatesShuffle2D(int **data, int num_row, int num_col);
    void GenerateChessBoard(int row, int col);
    int ExpandJudge(int row, int col, int *cnt_mine);
    int ExpandDFS(int row, int col, int *blk_expanded);
    int BlockExpand(int row, int col, int *blk_expanded);

private:
    int num_row;    //number of chessboard row
    int num_col;    //number of chessboard column
    int num_mine;   //number of chessboard mine
    int num_flag;   //number of flag
    int num_blkleft;//number of block left
    int runtime;    //current game runtime in second
    int game_sta;   //game status


};



#endif/*CHESSBOARD_H*/
// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


