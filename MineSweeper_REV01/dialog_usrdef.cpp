// =============================================================================
// File Name    : dialog_usrdef.cpp
// Project      : minesweeper
// Brief        : Source file for user-define dialog window.
// -----------------------------------------------------------------------------
// Version      Date            Coded by            Contents
// 0.0.1        Jul 11th, 2020  Mackie Xiao         create new
//
// =============================================================================
// End Revision
// =============================================================================
#include "ui_dialog_usrdef.h"
#include "dialog_usrdef.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QIcon>


// =========================================================
// Brief	: Constructor for class Dialog_UsrDef
// Arg		:
//  @*parent: pointer to parent class
// Retval	: none
// =========================================================
Dialog_UsrDef::Dialog_UsrDef(QWidget *parent):QDialog(parent),ui(new Ui::Dialog_UsrDef) {
    QString str, num1, num2;
    ui->setupUi(this);
    this->input_row = 0;
    this->input_col = 0;
    this->input_mine= 0;

    //label row
    num1 = QString::number(NUM_ROW_MIN, 10);
    num2 = QString::number(NUM_ROW_MAX, 10);
    str = "Number of row["+num1+"-"+num2+"]";
    ui->label_row->setText(str);

    //label column
    num1 = QString::number(NUM_COL_MIN, 10);
    num2 = QString::number(NUM_COL_MAX, 10);
    str = "Number of column["+num1+"-"+num2+"]";
    ui->label_col->setText(str);

    //label mine
    num1 = QString::number(NUM_MINE_MIN, 10);
    num2 = QString::number(NUM_MINE_MAX, 10);
    str = "Number of mine["+num1+"-"+num2+"]";
    ui->label_mine->setText(str);

    this->setWindowTitle("User-define");
}



// =========================================================
// Brief	: Destructor for class Dialog_UsrDef
// Arg		: void
// Retval	: none
// =========================================================
Dialog_UsrDef::~Dialog_UsrDef() {
    delete ui;
}


// =========================================================
// Brief	: buttonBox accepted slot function
// Arg		: void
// Retval	: none
// =========================================================
void Dialog_UsrDef::on_buttonBox_accepted(void) {
    bool ok, pass = true;
    QString str;

    //input row
    str = ui->lineEdit_row->text();
    this->input_row = str.toInt(&ok);
    if(true!=ok || NUM_ROW_MIN>this->input_row || NUM_ROW_MAX<this->input_row) pass = false;

    //input col
    str = ui->lineEdit_col->text();
    this->input_col = str.toInt(&ok);
    if(true == pass) {
        if(true!=ok || NUM_COL_MIN>this->input_col || NUM_COL_MAX<this->input_col) pass = false;
    }

    //input mine
    str = ui->lineEdit_mine->text();
    this->input_mine = str.toInt(&ok);
    if(true == pass) {
        if(true!=ok || NUM_MINE_MIN>this->input_mine || (this->input_row*this->input_col)-1<this->input_mine) pass = false;
    }

    //whether input wrong parameter
    if(false == pass) {
        QMessageBox message(QMessageBox::NoIcon, "Warning", "Input parameters error.");
        message.setWindowIcon(QIcon(RES_PATH_ICON));
        message.exec();
    }
    else
        ReGenerateChessBoard(this->input_row, this->input_col, this->input_mine);
}



// =========================================================
// Brief	: lineEdit_row editing finished slot function
// Arg		: void
// Retval	: none
// =========================================================
void Dialog_UsrDef::on_lineEdit_row_editingFinished(void) {
    bool ok;

    QString str = ui->lineEdit_row->text();
    this->input_row = str.toInt(&ok);

    if(true!=ok || NUM_ROW_MIN>this->input_row || NUM_ROW_MAX<this->input_row) {
        ui->lineEdit_row->setStyleSheet(QString("border: 2px solid #ff0000;border-radius: 10px;padding: 2px 5px;"));
    }
    else {
        ui->lineEdit_row->setStyleSheet(QString("border: 2px groove gray;border-radius: 10px;padding: 2px 5px;"));
    }

    int num_blk = this->input_row*this->input_col;
    if(0 != num_blk) {
        QString num1, num2;
        num1 = QString::number(NUM_MINE_MIN, 10);
        num2 = QString::number(num_blk-1, 10);
        QString tmp = "Number of mine["+num1+"-" + num2 + "]";
        ui->label_mine->setText(tmp);
        if(true!=ok || NUM_MINE_MIN>this->input_mine || num_blk-1<this->input_mine)
            ui->lineEdit_mine->setStyleSheet(QString("border: 2px solid #ff0000;border-radius: 10px;padding: 2px 5px;"));
        else
            ui->lineEdit_mine->setStyleSheet(QString("border: 2px groove gray;border-radius: 10px;padding: 2px 5px;"));
        update();
    }
}



// =========================================================
// Brief	: lineEdit_col editing finished slot function
// Arg		: void
// Retval	: none
// =========================================================
void Dialog_UsrDef::on_lineEdit_col_editingFinished() {
    bool ok;


    QString str = ui->lineEdit_col->text();
    this->input_col = str.toInt(&ok);

    if(true!=ok || NUM_COL_MIN>this->input_col || NUM_COL_MAX<this->input_col)
        ui->lineEdit_col->setStyleSheet(QString("border: 2px solid #ff0000;border-radius: 10px;padding: 2px 5px;"));
    else
        ui->lineEdit_col->setStyleSheet(QString("border: 2px groove gray;border-radius: 10px;padding: 2px 5px;"));

    int num_blk = this->input_row*this->input_col;
    if(0 != num_blk) {
        QString num1, num2;
        num1 = QString::number(NUM_MINE_MIN, 10);
        num2 = QString::number(num_blk-1, 10);
        QString tmp = "Number of mine["+num1+"-" + num2 + "]";
        ui->label_mine->setText(tmp);
        if(true!=ok || NUM_MINE_MIN>this->input_mine || num_blk-1<this->input_mine)
            ui->lineEdit_mine->setStyleSheet(QString("border: 2px solid #ff0000;border-radius: 10px;padding: 2px 5px;"));
        else
            ui->lineEdit_mine->setStyleSheet(QString("border: 2px groove gray;border-radius: 10px;padding: 2px 5px;"));
        update();
    }
}



// =========================================================
// Brief	: lineEdit_mine editing finished slot function
// Arg		: void
// Retval	: none
// =========================================================
void Dialog_UsrDef::on_lineEdit_mine_editingFinished(void) {
    bool ok;

    QString str = ui->lineEdit_mine->text();
    this->input_mine = str.toInt(&ok);

    int num_blk=this->input_row*this->input_col;
    if(true!=ok || NUM_MINE_MIN>this->input_mine || num_blk-1<this->input_mine)
        ui->lineEdit_mine->setStyleSheet(QString("border: 2px solid #ff0000;border-radius: 10px;padding: 2px 5px;"));
    else
        ui->lineEdit_mine->setStyleSheet(QString("border: 2px groove gray;border-radius: 10px;padding: 2px 5px;"));
}




// =============================================================================
// End File Copyright@2020 by Mackie Xiao
// =============================================================================


