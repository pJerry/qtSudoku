#include "sudokuwidget.h"

SudokuWidget::SudokuWidget(QWidget *parent)
{
    board = new SudokuBoard();
    scene = new QGraphicsScene();
    view = new QGraphicsView(this);
    loader = new SudokuLoader("level/001.txt");
    input = new QLineEdit(this);

    QFont font;
    font.setPointSize(40);

    input->setMinimumSize(50, 50);
    input->setMaximumSize(50, 50);
    input->setMaxLength(1);
    input->setFont(font);
    input->hide();

    setMinimumHeight(512);
    setMaximumHeight(512);
    setMinimumWidth(512);
    setMaximumWidth(512);

    displayItems();

    scene->addItem(board);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);

    connect(input, SIGNAL(returnPressed()), this, SLOT(slotCheckInput()));
}

void SudokuWidget::displayItems()
{
    int offset = 4;
    int xoffset = 0;
    int yoffset = 0;

    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            yoffset++;
        }
        for (int col = 0; col < 9; col++) {
            items[row][col] = new SudokuItem();
            connect(items[row][col], SIGNAL(signalOnClick(int, int)), this, SLOT(slotInputNumber(int, int)));

            if (col % 3 == 0 && col != 0) {
                xoffset++;
            }
            int temp_num = loader->getNumber(row, col);
            qDebug() << "Row: " << row << "Col: " << col << "Num: " << temp_num;

            if (temp_num == 0) {
                items[row][col]->setStatus(false);
            } else {
                items[row][col]->setStatus(true);
            }

            items[row][col]->setX((col*56)+(offset*xoffset));
            items[row][col]->setY((row*56)+(offset*yoffset));
            items[row][col]->setRow(row+1);
            items[row][col]->setCol(col+1);
            items[row][col]->setNumber(temp_num);
            scene->addItem(items[row][col]);
        }
        xoffset = 0;
    }
}

void SudokuWidget::loadSudoku()
{

}

void SudokuWidget::slotInputNumber(int row, int col)
{
    input->clear();

    if(!items[row-1][col-1]->getStatus()) {
        int x = items[row-1][col-1]->pos().x()+3;
        int y = items[row-1][col-1]->pos().y()+3;

        input->setGeometry(x, y, 50, 50);

        qDebug() << "INPUT: " << input->rect();
        qDebug() << "Row: " << row << "Col: " << col;

        tempRow = row-1;
        tempCol = col-1;

        input->show();
        input->setFocus();
    } else {
        input->hide();
    }

}

void SudokuWidget::slotCheckInput()
{
    input->hide();

    int num = input->text().toInt();

    if (items[tempRow][tempCol]->getNumber() == 0) {
        items[tempRow][tempCol]->setNumber(num);
        items[tempRow][tempCol]->setStatus(true);
    }

    input->clear();
}
