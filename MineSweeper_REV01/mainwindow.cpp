// =============================================================================
// File Name    : mainwindow.cpp
// Project      : MineSweeper
// Brief        : Source file for mainwindow module.
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#include "mainwindow.h"



// =============================================================================
// Macro Define
// =============================================================================
//mouse button bit mask
#define BTN_BITMASK_LEFT    1
#define BTN_BITMASK_RIGHT   2
#define BTN_BITMASK_MIDDLE  4


// =============================================================================
// Global Variable
// =============================================================================
ChessBoard *chessboard = new ChessBoard(BLK_NUM_ROW_PRIMARY, BLK_NUM_COL_PRIMARY, MINE_NUM_PRIMARY);
MainWindow *app;
int window_size_width = 0;
int window_size_height = 0;
int btn_sta[3] = {0, 0, 0};             //mouse button status
int mouse_pos[2] = {0, 0};              //current mouse position
int mouse_event = MOUSE_EVENT_NONE;     //mouse latch event
int yellowboy_sta = 0;                  //yellow boy clicked status
int f_db_click = false;                 //double click flag, used to implement double click


// =========================================================
// Brief	: Constructor for class MainWindow
// Arg		:
//  @*parent: pointer to parent class
// Retval	: none
// =========================================================
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow) {
    //set ui pointer to this
    app = this;
    ui->setupUi(this);
    Init();
}



// =========================================================
// Brief	: Destructor for class MainWindow
// Arg		: void
// Retval	: none
// =========================================================
MainWindow::~MainWindow() {
    delete ui;
}



// =========================================================
// Brief	: Initialize game
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::Init(void) {
    //register resource file
    QResource::registerResource("res.rcc");

    //create a timer
    timer_global = new QTimer(this);
    timer_click = new QTimer(this);
    timer_click->setInterval(DB_CLICK_INTERVAL);
    connect(timer_global, SIGNAL(timeout()), this, SLOT(on_secondAdd()));
    connect(timer_global, SIGNAL(timeout()), this, SLOT(update()));
    connect(timer_click, SIGNAL(timeout()), this, SLOT(clear_dbFlag()));
    InitScene();
}



// =========================================================
// Brief	: Initialize game scene
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::InitScene(void) {
    //set window icon
    setWindowIcon(QIcon(RES_PATH_ICON));

    //set windows title
    setWindowTitle(GAME_TITLE);

    //set windows fixed size
    window_size_width = BLK_NUM_COL_PRIMARY*SIZE_BLK_WIDTH + 2*COORD_CHESBORD_COL + 2*SIZE_CHESBORD_MARGINE_WIDTH;
    window_size_height = COORD_CHESBORD_ROW+SIZE_CHESBORD_HEIGHT(chessboard->GetRowNumber())+5;
    setFixedSize(window_size_width, window_size_height);
}



// =========================================================
// Brief	: Mouse press event
// Arg		:
//  @*event : mouse event
// Retval	: none
// =========================================================
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //collect mouse button status and position
    btn_sta[0] = event->buttons()&BTN_BITMASK_LEFT;
    btn_sta[1] = (event->buttons()&BTN_BITMASK_RIGHT)>>1;
    btn_sta[2] = (event->buttons()&BTN_BITMASK_MIDDLE)>>2;
    mouse_pos[0] = event->x();
    mouse_pos[1] = event->y();

    //update mouse event
    if((btn_sta[0]&&btn_sta[1]) || btn_sta[2])
        mouse_event = MOUSE_EVENT_EXPAND;
    else if(btn_sta[0]) {
        mouse_event = MOUSE_EVENT_SELECT;
        if(false == f_db_click) {
            f_db_click = true;
            this->timer_click->start();
        }
        else {
            mouse_event = MOUSE_EVENT_EXPAND;
            clear_dbFlag();
        }
    }
    else if(btn_sta[1])
        mouse_event = MOUSE_EVENT_FLAG;

    //yellow boy click handler
    if(MOUSE_EVENT_SELECT == mouse_event){
        if((COORD_YELLOWBOY_COL(window_size_width))<=mouse_pos[0] &&
           (COORD_YELLOWBOY_COL(window_size_width))+SIZE_YELLOWBOY_WIDTH>=mouse_pos[0] &&
           COORD_YELLOWBOY_ROW<=mouse_pos[1] && COORD_YELLOWBOY_ROW+SIZE_YELLOWBOY_HEIGHT>=mouse_pos[1])
            yellowboy_sta = 1;
        else
            yellowboy_sta = 0;
    }

    //update ui
    update();
}



// =========================================================
// Brief	: Mouse move event
// Arg		:
//  @*event : mouse event
// Retval	: none
// =========================================================
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //collection mouse button position
    mouse_pos[0] = event->x();
    mouse_pos[1] = event->y();

    //update mouse event
    if((btn_sta[0]&&btn_sta[1]) || btn_sta[2])
        mouse_event = MOUSE_EVENT_EXPAND;
    else if(btn_sta[0]) {
        if(MOUSE_EVENT_EXPAND != mouse_event)
            mouse_event = MOUSE_EVENT_SELECT;
    }

    //yellow boy click handler
    if(MOUSE_EVENT_SELECT == mouse_event){
        if((COORD_YELLOWBOY_COL(window_size_width))<=mouse_pos[0] &&
           (COORD_YELLOWBOY_COL(window_size_width))+SIZE_YELLOWBOY_WIDTH>=mouse_pos[0] &&
           COORD_YELLOWBOY_ROW<=mouse_pos[1] && COORD_YELLOWBOY_ROW+SIZE_YELLOWBOY_HEIGHT>=mouse_pos[1])
            yellowboy_sta = 1;
        else
            yellowboy_sta = 0;
    }

    //update ui
    update();
}



// =========================================================
// Brief	: Mouse release event
// Arg		:
//  @*event : mouse event
// Retval	: none
// =========================================================
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //calculate row and column position
    int col = (mouse_pos[0]-COORD_CHESBORD_COL-SIZE_CHESBORD_MARGINE_WIDTH);
    int row = (mouse_pos[1]-COORD_CHESBORD_ROW-SIZE_CHESBORD_MARGINE_WIDTH);
    if(col>0 && row>0) {
        col /= SIZE_BLK_WIDTH;
        row /= SIZE_BLK_HEIGHT;
    }

    //collect mouse button status and position
    btn_sta[0] = event->buttons()&BTN_BITMASK_LEFT;
    btn_sta[1] = (event->buttons()&BTN_BITMASK_RIGHT)>>1;
    btn_sta[2] = (event->buttons()&BTN_BITMASK_MIDDLE)>>2;
    mouse_pos[0] = event->x();
    mouse_pos[1] = event->y();

    //update mouse event
    if((btn_sta[0]&&btn_sta[1]) || btn_sta[2])
        mouse_event = MOUSE_EVENT_EXPAND;
    else if(btn_sta[0]) {
        if(MOUSE_EVENT_EXPAND != mouse_event)
            mouse_event = MOUSE_EVENT_SELECT;
    }
    else if(btn_sta[1]) {
        if(MOUSE_EVENT_EXPAND != mouse_event)
            mouse_event = MOUSE_EVENT_SELECT;
    }
    else {
        int sta = chessboard->GetGameStatus();
        if(GAME_STA_OVER!=chessboard->GetGameStatus() && GAME_STA_PASS!=chessboard->GetGameStatus())
            chessboard->UpdateChessBoard(row, col, mouse_event, 1);
        if(GAME_STA_PENDING==sta&&GAME_STA_PLAYING==chessboard->GetGameStatus()&&MOUSE_EVENT_SELECT==mouse_event)
            timer_global->start(1000);

        mouse_event = MOUSE_EVENT_NONE;
    }

    //stop the timer of game passed or over
    if(GAME_STA_OVER==chessboard->GetGameStatus() || GAME_STA_PASS==chessboard->GetGameStatus())
        timer_global->stop();

    //yellow boy click handler
    if(MOUSE_EVENT_NONE==mouse_event && 1==yellowboy_sta) {
        if((COORD_YELLOWBOY_COL(window_size_width))<=mouse_pos[0] &&
           (COORD_YELLOWBOY_COL(window_size_width))+SIZE_YELLOWBOY_WIDTH>=mouse_pos[0] &&
           COORD_YELLOWBOY_ROW<=mouse_pos[1] && COORD_YELLOWBOY_ROW+SIZE_YELLOWBOY_HEIGHT>=mouse_pos[1]) {
            timer_global->stop();
            clear_dbFlag();
            chessboard->UpdateChessBoard(0, 0, 0, 0);
        }
        yellowboy_sta = 0;
    }


    //update ui
    update();
}



// =========================================================
// Brief	: Paint event handler
// Arg		:
//  @*event : pointer to paint event
// Retval	: none
// =========================================================
void MainWindow::paintEvent(QPaintEvent *event) {
    event = event;//unused parameter

    QPainter painter(this);

    //load rescource file
    QPixmap background(RES_PATH_BKGND);
    QPixmap margin_up(RES_PATH_MARGIN_UP);
    QPixmap margin_dn(RES_PATH_MARGIN_DN);
    QPixmap margin_right(RES_PATH_MARGIN_RIGHT);
    QPixmap margin_left(RES_PATH_MARGIN_LEFT);
    QPixmap title_angle(RES_PATH_TITLE_ANGLE);
    QPixmap chesbord_angle(RES_PATH_CHESBORD_ANGLE);
    QPixmap cnt_bkgnd(RES_PATH_CNT_BKGND);
    QPixmap blk_1(RES_PATH_BLK_1);
    QPixmap blk_2(RES_PATH_BLK_2);
    QPixmap blk_3(RES_PATH_BLK_3);
    QPixmap blk_4(RES_PATH_BLK_4);
    QPixmap blk_5(RES_PATH_BLK_5);
    QPixmap blk_6(RES_PATH_BLK_6);
    QPixmap blk_7(RES_PATH_BLK_7);
    QPixmap blk_8(RES_PATH_BLK_8);
    QPixmap blk_open(RES_PATH_BLK_OPEN);
    QPixmap blk_close(RES_PATH_BLK_CLOSE);
    QPixmap blk_mine(RES_PATH_BLK_MINE);
    QPixmap blk_boom(RES_PATH_BLK_BOOM);
    QPixmap blk_wrongmine(RES_PATH_BLK_WRONGMINE);
    QPixmap blk_question(RES_PATH_BLK_QUESTION);
    QPixmap blk_flag(RES_PATH_BLK_FLAG);
    QPixmap cnt_0(RES_PATH_CNT_0);
    QPixmap cnt_1(RES_PATH_CNT_1);
    QPixmap cnt_2(RES_PATH_CNT_2);
    QPixmap cnt_3(RES_PATH_CNT_3);
    QPixmap cnt_4(RES_PATH_CNT_4);
    QPixmap cnt_5(RES_PATH_CNT_5);
    QPixmap cnt_6(RES_PATH_CNT_6);
    QPixmap cnt_7(RES_PATH_CNT_7);
    QPixmap cnt_8(RES_PATH_CNT_8);
    QPixmap cnt_9(RES_PATH_CNT_9);
    QPixmap cnt_none(RES_PATH_CNT_NONE);
    QPixmap yellowboy_smile(RES_PATH_YELLOWBOY_SMILE);
    QPixmap yellowboy_cool(RES_PATH_YELLOWBOY_COOL);
    QPixmap yellowboy_lose(RES_PATH_YELLOWBOY_LOSE);
    QPixmap yellowboy_look_dn(RES_PATH_YELLOWBOY_LOOK_DN);
    QPixmap yellowboy_look_up(RES_PATH_YELLOWBOY_LOOK_UP);
    QPixmap *p_temp = NULL;

    int size_width=0;



    //draw background
    QSize size(window_size_width, window_size_height);
    painter.drawPixmap(0, 0, background.scaled(size), 0, 0, window_size_width, window_size_height);



    //draw title margin
    size.setWidth(SIZE_TITLE_WIDTH(window_size_width));
    painter.drawPixmap(COORD_TITLE_UP_COL, COORD_TITLE_UP_ROW,
                       margin_up.scaled(size), 0, 0,
                       SIZE_TITLE_WIDTH(window_size_width), SIZE_TITLE_MARGIN_WIDTH);
    painter.drawPixmap(COORD_TITLE_DN_COL, COORD_TITLE_DN_ROW,
                       margin_dn.scaled(size), 0, 0,
                       size_width, SIZE_TITLE_MARGIN_WIDTH);
    painter.drawPixmap(COORD_TITLE_LEFT_COL, COORD_TITLE_RIGHT_ROW,
                       margin_left, 0, 0,
                       SIZE_TITLE_MARGIN_WIDTH, SIZE_TITLE_HEIGHT);
    painter.drawPixmap(COORD_TITLE_RIGHT_COL(window_size_width), COORD_TITLE_RIGHT_ROW,
                       margin_right, 0, 0,
                       SIZE_TITLE_MARGIN_WIDTH, SIZE_TITLE_HEIGHT);
    painter.drawPixmap(COORD_TITLE_ANGLE_DL_COL, COORD_TITLE_ANGLE_DL_ROW,
                       title_angle, 0, 0,
                       SIZE_TITLE_ANGLE_WIDTH, SIZE_TITLE_ANGLE_HEIGHT);
    painter.drawPixmap(COORD_TITLE_ANGLE_UR_COL(window_size_width), COORD_TITLE_ANGLE_UR_ROW,
                       title_angle, 0, 0,
                       SIZE_TITLE_ANGLE_WIDTH, SIZE_TITLE_ANGLE_HEIGHT);



    //draw chessboard margin
    size.setWidth(SIZE_CHESBORD_WIDTH(chessboard->GetColNumber()));
    size.setHeight(SIZE_CHESBORD_MARGINE_WIDTH);
    painter.drawPixmap(COORD_CHESBORD_UP_COL, COORD_CHESBORD_ROW,
                       margin_up.scaled(size), 0, 0,
                       SIZE_CHESBORD_WIDTH(chessboard->GetColNumber()), SIZE_CHESBORD_MARGINE_WIDTH);
    painter.drawPixmap(COORD_CHESBORD_DN_COL, COORD_CHESBORD_DN_ROW(chessboard->GetRowNumber()),
                       margin_dn.scaled(size), 0, 0,
                       SIZE_CHESBORD_WIDTH(chessboard->GetColNumber()), SIZE_CHESBORD_MARGINE_WIDTH);
    size.setWidth(SIZE_CHESBORD_MARGINE_WIDTH);
    size.setHeight(SIZE_CHESBORD_HEIGHT(chessboard->GetRowNumber()));
    painter.drawPixmap(COORD_CHESBORD_LEFT_COL, COORD_CHESBORD_LEFT_ROW,
                       margin_left.scaled(size), 0, 0,
                       SIZE_CHESBORD_MARGINE_WIDTH, SIZE_CHESBORD_HEIGHT(chessboard->GetRowNumber()));
    painter.drawPixmap(COORD_CHESBORD_RIGHT_COL(chessboard->GetColNumber()), COORD_CHESBORD_RIGHT_ROW,
                       margin_right.scaled(size), 0, 0,
                       SIZE_CHESBORD_MARGINE_WIDTH, SIZE_CHESBORD_HEIGHT(chessboard->GetRowNumber()));
    painter.drawPixmap(COORD_CHESBORD_ANGLE_DL_COL, COORD_CHESBORD_ANGLE_DL_ROW(chessboard->GetRowNumber()),
                       chesbord_angle, 0, 0,
                       SIZE_CHESBORD_ANGLE_WIDTH, SIZE_CHESBORD_ANGLE_HEIGHT);
    painter.drawPixmap(COORD_CHESBORD_ANGLE_UR_COL(chessboard->GetColNumber()), COORD_CHESBORD_ANGLE_UR_ROW,
                       chesbord_angle, 0, 0,
                       SIZE_CHESBORD_ANGLE_WIDTH, SIZE_CHESBORD_ANGLE_HEIGHT);



    //draw cnt background
    painter.drawPixmap(COORD_MINE_IND_BKGND_COL, COORD_MINE_IND_BKGND_ROW,
                       cnt_bkgnd,
                       0, 0,
                       SIZE_CNT_BKGND_WIDTH, SIZE_CNT_BKGND_HEIGHT);
    painter.drawPixmap(COORD_TIME_IND_BKGND_COL(window_size_width), COORD_TIME_IND_BKGND_ROW,
                       cnt_bkgnd,
                       0, 0,
                       SIZE_CNT_BKGND_WIDTH, SIZE_CNT_BKGND_HEIGHT);



    //draw yellow boy
    if(true == yellowboy_sta)
        p_temp = &yellowboy_look_dn;
    else {
        if(GAME_STA_OVER ==chessboard->GetGameStatus())
            p_temp = &yellowboy_lose;
        else if(GAME_STA_PASS == chessboard->GetGameStatus())
            p_temp = &yellowboy_cool;
        else if(MOUSE_EVENT_NONE != mouse_event)
            p_temp = &yellowboy_look_up;
        else
            p_temp = &yellowboy_smile;

    }
    painter.drawPixmap(COORD_YELLOWBOY_COL(window_size_width), COORD_YELLOWBOY_ROW,
                       *p_temp,
                       0, 0,
                       SIZE_YELLOWBOY_WIDTH, SIZE_YELLOWBOY_HEIGHT);



    //draw mine indication
    int mine_left = chessboard->GetMineNumber()-chessboard->GetFlagNumber();
    if(999 < mine_left) {
        for(int cnt=2; cnt>=0; --cnt)
            painter.drawPixmap(COORD_MINE_IND_COL+cnt*SIZE_CNT_WIDTH, COORD_MINE_IND_ROW,
                               cnt_none,
                               0, 0,
                               SIZE_CNT_WIDTH, SIZE_CNT_HEIGHT);
    }
    else {
        int num = mine_left;
        for(int cnt=2; cnt>=0; --cnt) {
            switch(num%10) {
            case 0: p_temp = &cnt_0;break;
            case 1: p_temp = &cnt_1;break;
            case 2: p_temp = &cnt_2;break;
            case 3: p_temp = &cnt_3;break;
            case 4: p_temp = &cnt_4;break;
            case 5: p_temp = &cnt_5;break;
            case 6: p_temp = &cnt_6;break;
            case 7: p_temp = &cnt_7;break;
            case 8: p_temp = &cnt_8;break;
            case 9: p_temp = &cnt_9;break;
            default: break;
            }
            painter.drawPixmap(COORD_MINE_IND_COL+cnt*SIZE_CNT_WIDTH, COORD_MINE_IND_ROW,
                               *p_temp,
                               0, 0,
                               SIZE_CNT_WIDTH, SIZE_CNT_HEIGHT);
            num /= 10;
        }
    }



    //draw time indication
    if(999 < chessboard->GetRunTime()) {
        for(int cnt=2; cnt>=0; --cnt)
            painter.drawPixmap(COORD_TIME_IND_COL(window_size_width)+cnt*SIZE_CNT_WIDTH, COORD_TIME_IND_ROW,
                               cnt_none,
                               0, 0,
                               SIZE_CNT_WIDTH, SIZE_CNT_HEIGHT);
    }
    else {
        int time = chessboard->GetRunTime();
        for(int cnt=2; cnt>=0; --cnt) {
            switch(time%10) {
            case 0: p_temp = &cnt_0;break;
            case 1: p_temp = &cnt_1;break;
            case 2: p_temp = &cnt_2;break;
            case 3: p_temp = &cnt_3;break;
            case 4: p_temp = &cnt_4;break;
            case 5: p_temp = &cnt_5;break;
            case 6: p_temp = &cnt_6;break;
            case 7: p_temp = &cnt_7;break;
            case 8: p_temp = &cnt_8;break;
            case 9: p_temp = &cnt_9;break;
            default:break;
            }
            painter.drawPixmap(COORD_TIME_IND_COL(window_size_width)+cnt*SIZE_CNT_WIDTH, COORD_TIME_IND_ROW,
                               *p_temp,
                               0, 0,
                               SIZE_CNT_WIDTH, SIZE_CNT_HEIGHT);
            time /= 10;
        }
    }



    //draw chessboard
    for(int cnt1=0; cnt1<chessboard->GetRowNumber(); ++cnt1)
        for(int cnt2=0; cnt2<chessboard->GetColNumber(); ++cnt2) {
            switch(chessboard->p_mask[cnt1][cnt2]) {
            case BLK_MASK_CLOSE     : p_temp = &blk_close;break;
            case BLK_MASK_FLAG      : p_temp = &blk_flag;break;
            case BLK_MASK_BOOM      : p_temp = &blk_boom;break;
            case BLK_MASK_WRONGMINE : p_temp = &blk_wrongmine;break;
            case BLK_MASK_QUESTION  : p_temp = &blk_question;break;
            case BLK_MASK_OPEN      :
                switch(chessboard->p_chessboard[cnt1][cnt2]) {
                case BLK_STA_NOMINE: p_temp = &blk_open;break;
                case BLK_STA_MINE:   p_temp = &blk_mine;break;
                case 1: p_temp = &blk_1;break;
                case 2: p_temp = &blk_2;break;
                case 3: p_temp = &blk_3;break;
                case 4: p_temp = &blk_4;break;
                case 5: p_temp = &blk_5;break;
                case 6: p_temp = &blk_6;break;
                case 7: p_temp = &blk_7;break;
                case 8: p_temp = &blk_8;break;
                default:break;
                }
                break;
            default:break;
            }
            painter.drawPixmap(COORD_CHESBORD_COL+SIZE_CHESBORD_MARGINE_WIDTH+cnt2*SIZE_BLK_WIDTH,
                               COORD_CHESBORD_ROW+SIZE_CHESBORD_MARGINE_WIDTH+cnt1*SIZE_BLK_HEIGHT,
                               *p_temp, 0, 0,
                               SIZE_BLK_WIDTH, SIZE_BLK_HEIGHT);
        }



    //mouse latch handling
    int col = (mouse_pos[0]-COORD_CHESBORD_COL-SIZE_CHESBORD_MARGINE_WIDTH);
    int row = (mouse_pos[1]-COORD_CHESBORD_ROW-SIZE_CHESBORD_MARGINE_WIDTH);
    if(col>0 && row>0) {
        col /= SIZE_BLK_WIDTH;
        row /= SIZE_BLK_HEIGHT;
    }
    if(GAME_STA_OVER!=chessboard->GetGameStatus() && GAME_STA_PASS!=chessboard->GetGameStatus()) {
        if(MOUSE_EVENT_EXPAND == mouse_event) {
            if(row>=0 && row<chessboard->GetRowNumber() && col>=0 && col<chessboard->GetColNumber())
                    for(int cnt1=row-1; cnt1<=row+1; ++cnt1)
                        for(int cnt2=col-1; cnt2<=col+1; ++cnt2) {
                            //boundary condition
                            if(cnt1>=0 && cnt1<chessboard->GetRowNumber() && cnt2>=0 && cnt2<chessboard->GetColNumber())
                                if(BLK_MASK_CLOSE == chessboard->p_mask[cnt1][cnt2])
                                painter.drawPixmap(COORD_CHESBORD_COL+SIZE_CHESBORD_MARGINE_WIDTH+cnt2*SIZE_BLK_WIDTH,
                                                   COORD_CHESBORD_ROW+SIZE_CHESBORD_MARGINE_WIDTH+cnt1*SIZE_BLK_HEIGHT,
                                                   blk_open,
                                                   0, 0,
                                                   SIZE_BLK_WIDTH, SIZE_BLK_HEIGHT);
                        }
        }
        else if(MOUSE_EVENT_SELECT == mouse_event) {
            if(row>=0 && row<chessboard->GetRowNumber() && col>=0 && col<chessboard->GetColNumber())
                if(BLK_MASK_CLOSE == chessboard->p_mask[row][col])
                    painter.drawPixmap(COORD_CHESBORD_COL+SIZE_CHESBORD_MARGINE_WIDTH+col*SIZE_BLK_WIDTH,
                                       COORD_CHESBORD_ROW+SIZE_CHESBORD_MARGINE_WIDTH+row*SIZE_BLK_HEIGHT,
                                       blk_open,
                                       0, 0,
                                       SIZE_BLK_WIDTH, SIZE_BLK_HEIGHT);
        }
    }
}



// =========================================================
// Brief	: Timer slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_secondAdd(void) {
    chessboard->UpdateRunTime();
}



// =========================================================
// Brief	: Double click timer slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::clear_dbFlag(void) {
    f_db_click = false;
    this->timer_click->stop();
}



// =========================================================
// Brief	: Stop Timer
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::StopTimer(void) {
    timer_global->stop();
}



// =========================================================
// Brief	: Action:Primary slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionPrimary_triggered(void){
    ReGenerateChessBoard(BLK_NUM_ROW_PRIMARY, BLK_NUM_COL_PRIMARY, MINE_NUM_PRIMARY);
}



// =========================================================
// Brief	: Action:Middle slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionMiddle_triggered(void) {
    ReGenerateChessBoard(BLK_NUM_ROW_MIDDLE, BLK_NUM_COL_MIDDLE, MINE_NUM_MIDDLE);
}



// =========================================================
// Brief	: Action:Senior slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionSenior_triggered(void) {
    ReGenerateChessBoard(BLK_NUM_ROW_SENIOR, BLK_NUM_COL_SENIOR, MINE_NUM_SENIOR);
}



// =========================================================
// Brief	: Action:Quit slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionQuit_triggered(void) {
    QApplication::quit();
}



// =========================================================
// Brief	: Action:How to play slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionHow_to_play_triggered(void)
{
    QMessageBox message(QMessageBox::NoIcon, "How to play", "The answer is beneathe your mouse. Try to click some.^_^");
    message.setWindowIcon(QIcon(RES_PATH_ICON));
    message.exec();
}



// =========================================================
// Brief	: Action:About MineSweeper slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionAbout_MineSweeper_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "About MineSweeper",
                        "Version: V1.0(Jul 19th,2020)\nAuthor: Mackie Xiao\nSource code please visit:\nhttps://github.com/MackieXiao");
    message.setWindowIcon(QIcon(RES_PATH_ICON));
    message.exec();
}



// =========================================================
// Brief	: Action:User-defined slot function
// Arg		: void
// Retval	: none
// =========================================================
void MainWindow::on_actionUser_defined_triggered()
{
    Dialog_UsrDef *test = new Dialog_UsrDef(this);
    test->show();
}



// =========================================================
// Brief	: Regenerate chessboard
// Arg		:
//  @row    : number of row
//  @col    : number of column
//  @mine   : number of mine
// Retval	: none
// =========================================================
void ReGenerateChessBoard(int row, int col, int mine)
{
    //stop timer
    app->StopTimer();

    //delete chessboard class
    delete chessboard;
    chessboard = new ChessBoard(row, col, mine);

    //set windows fixed size
    window_size_width = chessboard->GetColNumber()*SIZE_BLK_WIDTH + 2*COORD_CHESBORD_COL + 2*SIZE_CHESBORD_MARGINE_WIDTH;
    window_size_height = COORD_CHESBORD_ROW+SIZE_CHESBORD_HEIGHT(chessboard->GetRowNumber())+5;
    app->setFixedSize(window_size_width, window_size_height);

    //update ui
    app->update();
}


// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


