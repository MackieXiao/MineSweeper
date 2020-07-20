// =============================================================================
// File Name    : main.cpp
// Project      : minesweeper
// Brief        : Main file
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#include "mainwindow.h"
#include <QApplication>



// =========================================================
// Brief	: Main entrance
// Arg      :
//  @argc   : number of arguments
//  @argv   : pointer to arguments
// Retval	: exit status
// =========================================================
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


