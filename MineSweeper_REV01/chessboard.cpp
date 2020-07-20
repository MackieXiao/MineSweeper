// =============================================================================
// File Name    : chessboard.cpp
// Project      : minesweeper
// Brief        : Source file for the logic layer of chessboard.
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#include "chessboard.h"

using namespace std;

// =========================================================
// Brief	: Constructor of class "chessboard"
// Arg      :
//  @row    : number of chessboard row
//  @col    : number of chessboard column
//  @mine   : number of chessboard mine
// Retval	: none
// =========================================================
ChessBoard::ChessBoard(int row, int col, int mine) {
    //initialize private member
    this->num_col    = col;
    this->num_row    = row;
    this->num_mine   = mine;
    this->num_flag   = 0;
    this->num_blkleft= col*row;
    this->runtime    = 0;
    this->game_sta   = GAME_STA_PENDING;

    //allocate a new memory for chessboard array and mask array
    p_chessboard = new int *[row];
    p_mask       = new int *[row];
    for(int cnt=0; cnt<row; ++cnt) {
        p_chessboard[cnt] = new int [col];
        p_mask[cnt] = new int [col];
    }

    //initialize chessboard and mask array
    for(int cnt1=0; cnt1<row; ++cnt1)
        for(int cnt2=0; cnt2<col; ++cnt2) {
            p_chessboard[cnt1][cnt2] = BLK_STA_NOMINE;
            p_mask[cnt1][cnt2] = BLK_MASK_CLOSE;
        }
}



// =========================================================
// Brief	: Destructor of class "chessboard"
// Arg      : void
// Retval	: none
// =========================================================
ChessBoard::~ChessBoard() {
    for(int cnt=0; cnt<this->num_row; ++cnt) {
        delete[] p_chessboard[cnt];
        delete[] p_mask[cnt];
    }
    delete[] p_chessboard;
    delete[] p_mask;
}



// =========================================================
// Brief	: Update chessboard block logic
// Arg      :
//  @pos_row    : active row block position
//  @pos_col    : active column block position
//  @mouse_event: active mouse event
//  @f_start    : start flag. 1 for game start, 0 for only initialize
// Retval	: none
// =========================================================
void ChessBoard::UpdateChessBoard(int pos_row, int pos_col, int mouse_event, int f_start) {
    if(pos_col<0||pos_col>=this->num_col||pos_row<0||pos_row>=this->num_row) return;

    if(1 != f_start) {
        this->game_sta = GAME_STA_PENDING;
        this->num_flag = 0;
        this->num_blkleft = this->num_row*this->num_col;
        this->runtime = 0;
        GenerateChessBoard(pos_row, pos_col);
        return;
    }

    //handle mouse event
    switch(mouse_event) {
    //select event
    case MOUSE_EVENT_SELECT:
        switch(this->game_sta) {
        case GAME_STA_PENDING:
        case GAME_STA_PASS:
        case GAME_STA_OVER:
            int tmp;
            GenerateChessBoard(pos_row, pos_col);
            this->game_sta = GAME_STA_PLAYING;
            this->num_flag = 0;
            BlockExpand(pos_row, pos_col, &tmp);
            this->num_blkleft -= tmp;
            break;
        case GAME_STA_PLAYING:
            if(BLK_MASK_FLAG==this->p_mask[pos_row][pos_col] || BLK_MASK_QUESTION==p_mask[pos_row][pos_col])
                break;
            else if(BLK_STA_MINE==this->p_chessboard[pos_row][pos_col]) {
                this->p_mask[pos_row][pos_col] = BLK_MASK_BOOM;
                this->game_sta = GAME_STA_OVER;
            }
            else {
                if(BLK_STA_NOMINE == this->p_chessboard[pos_row][pos_col]) {
                    int tmp, ret;
                    ret = BlockExpand(pos_row, pos_col, &tmp);
                    this->num_blkleft -= tmp;
                    if(-1 == ret)
                        this->game_sta = GAME_STA_OVER;
                }
                else if(BLK_MASK_CLOSE == this->p_mask[pos_row][pos_col]){
                    this->p_mask[pos_row][pos_col] = BLK_MASK_OPEN;
                    --this->num_blkleft;
                }
            }
            break;
        default: break;
        }
        break;
    //expand event
    case MOUSE_EVENT_EXPAND:
        if(BLK_MASK_CLOSE!=p_mask[pos_row][pos_col]&&BLK_MASK_FLAG!=p_mask[pos_row][pos_col]) {
            int tmp, ret;
            ret = BlockExpand(pos_row, pos_col, &tmp);
            this->num_blkleft -= tmp;
            if(-1 == ret)
                this->game_sta = GAME_STA_OVER;

        }
        break;
    //flag event
    case MOUSE_EVENT_FLAG:
        if(BLK_MASK_CLOSE == p_mask[pos_row][pos_col]) {
            if(this->num_mine > this->num_flag) {
                p_mask[pos_row][pos_col] = BLK_MASK_FLAG;
                ++this->num_flag;
            }
        }
        else if(BLK_MASK_FLAG == p_mask[pos_row][pos_col]) {
            p_mask[pos_row][pos_col] = BLK_MASK_QUESTION;
        }
        else if(BLK_MASK_QUESTION == p_mask[pos_row][pos_col]) {
            p_mask[pos_row][pos_col] = BLK_MASK_CLOSE;
            --this->num_flag;
        }
        break;
    }

    //If the game is over, open all the unrevaled blocks that contain mine and
    //mark the flaged block that not contains mine.
    //If the game is passed, flag all the unrevealed blocks that contain mine
    if(GAME_STA_OVER == this->game_sta) {
        for(int cnt1=0; cnt1<this->num_row; ++cnt1)
            for(int cnt2=0; cnt2<this->num_col; ++cnt2) {
                if(BLK_STA_MINE==this->p_chessboard[cnt1][cnt2]&&
                   BLK_MASK_FLAG!=this->p_mask[cnt1][cnt2] &&
                   BLK_MASK_BOOM!=this->p_mask[cnt1][cnt2])
                    p_mask[cnt1][cnt2] = BLK_MASK_OPEN;
                else if(BLK_MASK_FLAG==this->p_mask[cnt1][cnt2]&&BLK_STA_MINE!=this->p_chessboard[cnt1][cnt2])
                    this->p_mask[cnt1][cnt2] = BLK_MASK_WRONGMINE;
            }
    }
    //game pass condition: block left is equal to number of mine
    else if(this->num_blkleft == this->num_mine) {
        for(int cnt1=0; cnt1<this->num_row; ++cnt1)
            for(int cnt2=0; cnt2<this->num_col; ++cnt2)
                if(BLK_MASK_CLOSE==this->p_mask[cnt1][cnt2] || BLK_MASK_QUESTION==this->p_mask[cnt1][cnt2])
                    this->p_mask[cnt1][cnt2] = BLK_MASK_FLAG;
        this->num_flag = this->num_mine;
        this->game_sta = GAME_STA_PASS;
    }
}



// =========================================================
// Brief	: Get chessboard row number
// Arg      : void
// Retval	: chessboard row number
// =========================================================
int ChessBoard::GetRowNumber() {
    return this->num_row;
}



// =========================================================
// Brief	: Get chessboard column number
// Arg      : void
// Retval	: chessboard column number
// =========================================================
int ChessBoard::GetColNumber() {
    return this->num_col;
}



// =========================================================
// Brief	: Get number of mine
// Arg      : void
// Retval	: number of mine
// =========================================================
int ChessBoard::GetMineNumber(void) {
    return this->num_mine;
}



// =========================================================
// Brief	: Get current runtime
// Arg      : void
// Retval	: current runtime in second
// =========================================================
int ChessBoard::GetRunTime() {
    return this->runtime;
}



// =========================================================
// Brief	: Update runtime
// Arg      : void
// Retval	: void
// =========================================================
void ChessBoard::UpdateRunTime(void) {
    ++this->runtime;
}



// =========================================================
// Brief	: Get current game status
// Arg      : void
// Retval	: current game status
// =========================================================
int ChessBoard::GetGameStatus(void) {
    return this->game_sta;
}



// =========================================================
// Brief	: Get flag number
// Arg      : void
// Retval	: flag number
// =========================================================
int ChessBoard::GetFlagNumber() {
    return this->num_flag;
}



// =====================Private Method====================

// =========================================================
// Brief	: 2D Fisher-Yates shuffle algorithm
// Arg      :
//  @**data : input 2d array
//  @row    : number of row
//  @col    : number of column
// Retval	: none
// =========================================================
void ChessBoard::FisherYatesShuffle2D(int **data, int row, int col) {
    //check data existence
    if(NULL == data)
        return;

    //calculate total size
    int size = row * col;

    //shuffle
    for(int cnt=size-1; cnt>0; --cnt) {
        srand((unsigned)time(0));//generate a seed
        int index = rand()%(cnt+1);
        swap(data[index/col][index%col], data[cnt/col][cnt%col]);
    }
}



// =========================================================
// Brief	: Generate chessboard mine distribution according
//            to the first active block
// Arg      :
//  @row    : row of the first active block
//  @col    : column of the first active block
// Retval	: none
// =========================================================
void ChessBoard::GenerateChessBoard(int row, int col) {
    vector<int> v_row, v_col;
    bool f_expand = (this->num_row*this->num_col-this->num_mine)<10 ? false : true;

    //construct vector array for unmined block recording
    for(int cnt=this->num_row*this->num_col-1; cnt>=0; --cnt)
        if((row*this->num_col)+col != cnt) {
            v_row.push_back(cnt/this->num_col);
            v_col.push_back(cnt%this->num_col);
        }

    //flush chessboard and mask
    for(int cnt1=0; cnt1<this->num_row; ++cnt1)
        for(int cnt2=0; cnt2<this->num_col; ++cnt2) {
            p_chessboard[cnt1][cnt2] = BLK_STA_NOMINE;
            p_mask[cnt1][cnt2] = BLK_MASK_CLOSE;
        }

    //generate chessboard mine distribution
    //Here we use v_row and v_col vector to store row and column of all the unmined block.
    //Once a random mine position is generated, v_row and v_col erase the block row and column info
    //to ensure the next random mine position is still in the remain unmined block.
    srand((unsigned)time(0));//generate a seed
    int cnt_mine = 0;
    while(cnt_mine != this->num_mine) {
        int num = rand()%v_row.size();
        if(true==f_expand && 1>=abs(v_row[num]-row) && 1>=abs(v_col[num]-col))
            continue;
        this->p_chessboard[v_row[num]][v_col[num]] = BLK_STA_MINE;
        v_row.erase(v_row.begin()+num);
        v_col.erase(v_col.begin()+num);
        ++cnt_mine;
    }

    //calculate mine indication number for each block
    for(int cnt1=0; cnt1<this->num_row; ++cnt1)
        for(int cnt2=0; cnt2<this->num_col; ++cnt2) {
            if(0 != p_chessboard[cnt1][cnt2])
                continue;

            //sub-block mine sum
            for(int cnt3=cnt1-1; cnt3<=cnt1+1; ++cnt3)
                for(int cnt4=cnt2-1; cnt4<=cnt2+1; ++cnt4) {
                    //boundary condition
                    if(cnt3>=0 && cnt3<this->num_row && cnt4>=0 && cnt4<this->num_col && BLK_STA_MINE==p_chessboard[cnt3][cnt4])
                        ++p_chessboard[cnt1][cnt2];
                }
        }
}



// =========================================================
// Brief	: Expand action to judge whether there are mines
//            surrouding to the active block
// Arg      :
//  @row    : row of the active block
//  @col    : column of the active block
//  @*cnt_mine: num of mine around the active block[o]
// Retval	: 0 for successed and -1 for failed
// =========================================================
int ChessBoard::ExpandJudge(int row, int col, int *cnt_mine) {
    if(NULL == cnt_mine) return -1;

    int cnt = 0;
    for(int cnt1=row-1; cnt1<=row+1; ++cnt1)
        for(int cnt2=col-1; cnt2<=col+1; ++cnt2) {
            //boudary condition
            if(cnt1>=0&&cnt1<this->num_row&&cnt2>=0&&cnt2<this->num_col) {
                if((BLK_STA_MINE==p_chessboard[cnt1][cnt2]&&BLK_MASK_FLAG!=p_mask[cnt1][cnt2]) ||
                   BLK_MASK_QUESTION==p_mask[cnt1][cnt2])
                    ++cnt;
                else if(BLK_STA_MINE!=p_chessboard[cnt1][cnt2]&&BLK_MASK_FLAG==p_mask[cnt1][cnt2]) {
                    p_mask[cnt1][cnt2] = BLK_MASK_WRONGMINE;
                    return -1;
                }
            }
        }
    *cnt_mine = cnt;
    return 0;
}



// =========================================================
// Brief	: DFS algorithm for expand action
// Arg      :
//  @row    : row of the active block
//  @col    : column of the active block
//  @*blk_expanded: number of expanded block in this iteration[o]
// Retval	: 0 for successed and -1 for failed
// =========================================================
int ChessBoard::ExpandDFS(int row, int col, int *blk_expanded) {
    int cnt_mine;

    //whether this block is been revealed
    if(BLK_MASK_OPEN != this->p_mask[row][col]) {
        p_mask[row][col] = BLK_MASK_OPEN;
        *blk_expanded += 1;
    }

    //whether there is irrational block around the active block
    if(-1 == ExpandJudge(row, col, &cnt_mine)) return -1;

    //whether there are mines around the active block
    if(0 != cnt_mine) return 0;

    //dfs iteration
    for(int cnt1=row-1; cnt1<=row+1; ++cnt1)
        for(int cnt2=col-1; cnt2<=col+1; ++cnt2) {
            if(cnt1>=0&&cnt1<this->num_row&&cnt2>=0&&cnt2<this->num_col&&BLK_MASK_CLOSE==p_mask[cnt1][cnt2])
                ExpandDFS(cnt1, cnt2, blk_expanded);
        }

    return 0;
}



// =========================================================
// Brief	: Expand action function
// Arg      :
//  @row    : row of the active block
//  @col    : column of the active block
//  @*blk_expanded: number of expanded block in this iteration[o]
// Retval	: 0 for successed and -1 for failed
// =========================================================
int ChessBoard::BlockExpand(int row, int col, int *blk_expanded) {
    int cnt_blk = 0;
    int ret = ExpandDFS(row, col, &cnt_blk);

    *blk_expanded = cnt_blk;

    return ret;
}



// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


