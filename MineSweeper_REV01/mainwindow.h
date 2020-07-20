// =============================================================================
// File Name    : mainwindow.h
// Project      : MineSweeper
// Brief        : Header file of mainwindow.c
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H



// =========================================================
// File Include
// =========================================================
#include "dialog_usrdef.h"
#include "ui_mainwindow.h"
#include "chessboard.h"
#include "config.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QResource>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSize>



namespace Ui {
class MainWindow;
}



// =========================================================
// Class Define
// =========================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init(void);
    void InitScene(void);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void StartTimer(void);
    void StopTimer(void);

private:
    QTimer *timer_global;
    QTimer *timer_click;

private slots:
    void on_secondAdd(void);
    void clear_dbFlag(void);
    void on_actionPrimary_triggered(void);
    void on_actionMiddle_triggered(void);
    void on_actionSenior_triggered(void);
    void on_actionQuit_triggered(void);
    void on_actionHow_to_play_triggered(void);
    void on_actionAbout_MineSweeper_triggered(void);
    void on_actionUser_defined_triggered(void);

private:
    Ui::MainWindow *ui;
};

void ReGenerateChessBoard(int row, int col, int mine);



#endif/*MAINWINDOW_H*/
// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================
