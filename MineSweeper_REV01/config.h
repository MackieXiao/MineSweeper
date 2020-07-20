// =============================================================================
// File Name    : config.h
// Project      : MineSweeper
// Brief        : This file defines the game configuration parameters of the project.
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#ifndef CONFIG_H
#define CONFIG_H



// =========================================================
// Macro Define
// =========================================================
//row, column and mine limitation
#define NUM_ROW_MAX                 40
#define NUM_ROW_MIN                 1
#define NUM_COL_MAX                 80
#define NUM_COL_MIN                 9
#define NUM_MINE_MAX                999
#define NUM_MINE_MIN                0


// chessboard block num for each difficulty
#define BLK_NUM_ROW_PRIMARY         9
#define BLK_NUM_COL_PRIMARY         9
#define BLK_NUM_ROW_MIDDLE          16
#define BLK_NUM_COL_MIDDLE          16
#define BLK_NUM_ROW_SENIOR          16
#define BLK_NUM_COL_SENIOR          30


//mine nume for each difficulty
#define MINE_NUM_PRIMARY            10
#define MINE_NUM_MIDDLE             40
#define MINE_NUM_SENIOR             99


//chessboard element size in pixcels
#define SIZE_BLK_WIDTH              21
#define SIZE_BLK_HEIGHT             21
#define SIZE_CNT_WIDTH              20
#define SIZE_CNT_HEIGHT             28
#define SIZE_YELLOWBOY_WIDTH        28
#define SIZE_YELLOWBOY_HEIGHT       28
#define SIZE_CNT_BKGND_WIDTH        64
#define SIZE_CNT_BKGND_HEIGHT       32


//game title
#define GAME_TITLE          "MineSweeper"


//title and chessboard size
#define SIZE_TITLE_WIDTH(window_width)          (window_width - 2*COORD_CHESBORD_COL)//this is depend on the window width
#define SIZE_TITLE_HEIGHT                       44
#define SIZE_TITLE_ANGLE_WIDTH                  SIZE_TITLE_MARGIN_WIDTH
#define SIZE_TITLE_ANGLE_HEIGHT                 SIZE_TITLE_MARGIN_WIDTH
#define SIZE_CHESBORD_WIDTH(num_col)            (num_col*SIZE_BLK_WIDTH+2*SIZE_CHESBORD_MARGINE_WIDTH)
#define SIZE_CHESBORD_HEIGHT(num_row)           (num_row*SIZE_BLK_HEIGHT+2*SIZE_CHESBORD_MARGINE_WIDTH)
#define SIZE_CHESBORD_ANGLE_WIDTH               SIZE_CHESBORD_MARGINE_WIDTH
#define SIZE_CHESBORD_ANGLE_HEIGHT              SIZE_CHESBORD_MARGINE_WIDTH


//margin width of title and chessboard
#define SIZE_TITLE_MARGIN_WIDTH                 2
#define SIZE_CHESBORD_MARGINE_WIDTH             3


//menuBar height in pixcels
#define MENUBAR_HEIGHT                          23


//double click time interval is ms
#define DB_CLICK_INTERVAL                       300


//coordination of title
#define COORD_TITLE_ROW                         (MENUBAR_HEIGHT+6)//top margin refer to maintoolbar down margin
#define COORD_TITLE_COL                         5//left margin refer to window left margin
#define COORD_TITLE_UP_ROW                      COORD_TITLE_ROW
#define COORD_TITLE_UP_COL                      COORD_TITLE_COL
#define COORD_TITLE_DN_ROW                      (COORD_TITLE_ROW+SIZE_TITLE_HEIGHT-SIZE_TITLE_MARGIN_WIDTH)//top margin refer to title down margin
#define COORD_TITLE_DN_COL                      COORD_TITLE_UP_COL
#define COORD_TITLE_RIGHT_ROW                   COORD_TITLE_ROW
#define COORD_TITLE_RIGHT_COL(window_width)     (window_width-COORD_CHESBORD_COL-SIZE_TITLE_MARGIN_WIDTH)//this is depend on the title width
#define COORD_TITLE_LEFT_ROW                    COORD_TITLE_RIGHT_ROW
#define COORD_TITLE_LEFT_COL                    COORD_TITLE_COL
#define COORD_TITLE_ANGLE_DL_ROW                COORD_TITLE_DN_ROW
#define COORD_TITLE_ANGLE_DL_COL                COORD_TITLE_LEFT_COL
#define COORD_TITLE_ANGLE_UR_ROW                COORD_TITLE_UP_ROW
#define COORD_TITLE_ANGLE_UR_COL(window_width)  (window_width-COORD_CHESBORD_COL-SIZE_TITLE_MARGIN_WIDTH)//this is depend on the title width


//coordination of mine and time indication background
#define COORD_MINE_IND_BKGND_ROW                (COORD_TITLE_ROW+SIZE_TITLE_MARGIN_WIDTH+4)
#define COORD_MINE_IND_BKGND_COL                (COORD_TITLE_COL+SIZE_TITLE_MARGIN_WIDTH+5)
#define COORD_TIME_IND_BKGND_ROW                COORD_MINE_IND_BKGND_ROW
#define COORD_TIME_IND_BKGND_COL(window_width)  (COORD_TITLE_RIGHT_COL(window_width)-SIZE_CNT_BKGND_WIDTH-5)//this is depend on the title width


//coorindation of mine and time indication refer to each background
#define COORD_MINE_IND_ROW                      (COORD_MINE_IND_BKGND_ROW+2)//element top margin refer to cnt background top margin
#define COORD_MINE_IND_COL                      (COORD_MINE_IND_BKGND_COL+2)//element left margin refer to mine indication background left margin
#define COORD_TIME_IND_ROW                      COORD_MINE_IND_ROW
#define COORD_TIME_IND_COL(window_width)        (COORD_TIME_IND_BKGND_COL(window_width)+2)


//coordination of yellow boy
#define COORD_YELLOWBOY_ROW                     COORD_MINE_IND_ROW
#define COORD_YELLOWBOY_COL(window_width)       (window_width/2-SIZE_YELLOWBOY_WIDTH/2)


//coordination of chessboard
#define COORD_CHESBORD_ROW                      (COORD_TITLE_ROW+SIZE_TITLE_HEIGHT+6)
#define COORD_CHESBORD_COL                      COORD_TITLE_COL
#define COORD_CHESBORD_UP_ROW                   COORD_CHESBORD_ROW
#define COORD_CHESBORD_UP_COL                   COORD_CHESBORD_COL
#define COORD_CHESBORD_DN_ROW(num_row)          (COORD_CHESBORD_ROW+SIZE_CHESBORD_MARGINE_WIDTH+num_row*SIZE_BLK_HEIGHT)
#define COORD_CHESBORD_DN_COL                   COORD_CHESBORD_UP_COL
#define COORD_CHESBORD_LEFT_ROW                 COORD_CHESBORD_UP_ROW
#define COORD_CHESBORD_LEFT_COL                 COORD_CHESBORD_UP_COL
#define COORD_CHESBORD_RIGHT_ROW                COORD_CHESBORD_UP_ROW
#define COORD_CHESBORD_RIGHT_COL(num_col)       (COORD_CHESBORD_LEFT_COL+SIZE_CHESBORD_MARGINE_WIDTH+num_col*SIZE_BLK_WIDTH)
#define COORD_CHESBORD_ANGLE_DL_ROW(num_row)    COORD_CHESBORD_DN_ROW(num_row)
#define COORD_CHESBORD_ANGLE_DL_COL             COORD_CHESBORD_DN_COL
#define COORD_CHESBORD_ANGLE_UR_ROW             COORD_CHESBORD_RIGHT_ROW
#define COORD_CHESBORD_ANGLE_UR_COL(num_col)    COORD_CHESBORD_RIGHT_COL(num_col)




//rescource file path
#define RES_PATH_ICON               ":/res/app.ico"
#define RES_PATH_BLK_1              ":/res/blk_1.bmp"
#define RES_PATH_BLK_2              ":/res/blk_2.bmp"
#define RES_PATH_BLK_3              ":/res/blk_3.bmp"
#define RES_PATH_BLK_4              ":/res/blk_4.bmp"
#define RES_PATH_BLK_5              ":/res/blk_5.bmp"
#define RES_PATH_BLK_6              ":/res/blk_6.bmp"
#define RES_PATH_BLK_7              ":/res/blk_7.bmp"
#define RES_PATH_BLK_8              ":/res/blk_8.bmp"
#define RES_PATH_BLK_OPEN           ":/res/blk_open.bmp"
#define RES_PATH_BLK_CLOSE          ":/res/blk_close.bmp"
#define RES_PATH_BLK_MINE           ":/res/blk_mine.bmp"
#define RES_PATH_BLK_BOOM           ":/res/blk_mineboom.bmp"
#define RES_PATH_BLK_WRONGMINE      ":/res/blk_wrongmine.bmp"
#define RES_PATH_BLK_QUESTION       ":/res/blk_question.bmp"
#define RES_PATH_BLK_FLAG           ":/res/blk_redflag.bmp"
#define RES_PATH_CNT_0              ":/res/cnt_0.bmp"
#define RES_PATH_CNT_1              ":/res/cnt_1.bmp"
#define RES_PATH_CNT_2              ":/res/cnt_2.bmp"
#define RES_PATH_CNT_3              ":/res/cnt_3.bmp"
#define RES_PATH_CNT_4              ":/res/cnt_4.bmp"
#define RES_PATH_CNT_5              ":/res/cnt_5.bmp"
#define RES_PATH_CNT_6              ":/res/cnt_6.bmp"
#define RES_PATH_CNT_7              ":/res/cnt_7.bmp"
#define RES_PATH_CNT_8              ":/res/cnt_8.bmp"
#define RES_PATH_CNT_9              ":/res/cnt_9.bmp"
#define RES_PATH_CNT_NONE           ":/res/cnt_none.bmp"
#define RES_PATH_YELLOWBOY_SMILE    ":/res/yellowboy_smile.bmp"
#define RES_PATH_YELLOWBOY_COOL     ":/res/yellowboy_cool.bmp"
#define RES_PATH_YELLOWBOY_LOSE     ":/res/yellowboy_lose.bmp"
#define RES_PATH_YELLOWBOY_LOOK_DN  ":/res/yellowboy_look_dn.bmp"
#define RES_PATH_YELLOWBOY_LOOK_UP  ":/res/yellowboy_look_up.bmp"
#define RES_PATH_CNT_BKGND          ":/res/cnt_background.bmp"
#define RES_PATH_BKGND              ":/res/background.bmp"
#define RES_PATH_MARGIN_UP          ":/res/margin_up.bmp"
#define RES_PATH_MARGIN_DN          ":/res/margin_dn.bmp"
#define RES_PATH_MARGIN_RIGHT       ":/res/margin_right.bmp"
#define RES_PATH_MARGIN_LEFT        ":/res/margin_left.bmp"
#define RES_PATH_TITLE_ANGLE        ":/res/title_angle.bmp"
#define RES_PATH_CHESBORD_ANGLE     ":/res/chessboard_angle.bmp"



#endif/*CONFIG_H*/
// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


