// =============================================================================
// File Name    : dialog_usrdef.h
// Project      : MineSweeper
// Brief        : Header file of dialog.c
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#ifndef DIALOG_USRDEF_H
#define DIALOG_USRDEF_H



// =========================================================
// File Include
// =========================================================
#include "config.h"
#include <QDialog>

namespace Ui {
class Dialog_UsrDef;
}



// =========================================================
// Class Define
// =========================================================
class Dialog_UsrDef : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_UsrDef(QWidget *parent = 0);
    ~Dialog_UsrDef();

private slots:
    void on_buttonBox_accepted(void);

    void on_lineEdit_row_editingFinished(void);

    void on_lineEdit_col_editingFinished(void);

    void on_lineEdit_mine_editingFinished(void);

private:
    Ui::Dialog_UsrDef *ui;
    int input_row;
    int input_col;
    int input_mine;

};

#endif/*DIALOG_USRDEF_H*/
// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


