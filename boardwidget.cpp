#include "boardwidget.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QSignalBlocker>
#include <iostream>

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
    boardLogic = new BoardLogic();

    boardWidget = new QTableWidget(9,9,this);

    boardWidget->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    boardWidget->verticalHeader()->setDefaultSectionSize(20);

    boardWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Fixed);
    boardWidget->horizontalHeader()->setDefaultSectionSize(20);

    boardWidget->setFixedSize(200,210);

    initSudoku();

    newSudokuButton = new QPushButton("New Sudoku", this);
    newSudokuButton->setGeometry(300, 10, 100, 20);

    connect(newSudokuButton, SIGNAL (clicked()), this, SLOT (slotCreateNewSudoku()));
    connect(boardWidget, SIGNAL (cellClicked(int,int)), this, SLOT (slotReturnCellNumber(int,int)));
    connect(boardWidget, SIGNAL (cellChanged(int,int)), this, SLOT (slotCheckEnteredNumber(int,int)));
}

void BoardWidget::initSudoku() {
    const QSignalBlocker blocker(boardWidget);

        for (int col = 0; col < 9; col++) {
            for (int row = 0; row < 9; row++) {
                boardWidget->setItem(row, col, new QTableWidgetItem(QString("")));
            }
        }
        displaySudoku();
}

void BoardWidget::displaySudoku() {
    const QSignalBlocker blocker(boardWidget);

    boardLogic->printBoard();

    Qt::ItemFlags flags;

    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            QString number = QString::number(boardLogic->getNumber(row, col));
            flags = boardWidget->item(row, col)->flags();

            if (number.toInt() != 0) {
                flags &= ~Qt::ItemIsEditable;

                boardWidget->item(row, col)->setText(number);
                boardWidget->item(row, col)->setBackgroundColor(Qt::green);
                boardWidget->item(row, col)->setFlags(flags);
            } else {
                flags |= Qt::ItemIsEditable;

                boardWidget->item(row, col)->setText(QString(""));
                boardWidget->item(row, col)->setBackgroundColor(Qt::white);
                boardWidget->item(row, col)->setFlags(flags);
            }
        }
    }
}

void BoardWidget::slotCreateNewSudoku() {
    boardLogic->generateEmptySudoku();
    boardLogic->generateSudoku();
    displaySudoku();
}

void BoardWidget::slotReturnCellNumber(int row, int col) {
    cout << "--------------------------------" << endl;
    boardLogic->getNumber(row, col);
    QString number = boardWidget->item(row, col)->text();
    cout << "[BoardWidget] Row: " << row << " Col: " << col << " Number: " << number.toStdString() << endl;
    cout << "--------------------------------" << endl;
}

void BoardWidget::slotCheckEnteredNumber(int row, int col) {
    // Store the entered in a QString
    QString qNumber = boardWidget->item(row, col)->text();
    boardLogic->insertNumber(row, col, qNumber.toInt());
    displaySudoku();
}