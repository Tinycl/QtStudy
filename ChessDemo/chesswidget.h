#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QWidget>

class ChessWidget : public QWidget
{
    Q_OBJECT

public:
    ChessWidget(QWidget *parent = 0);
    ~ChessWidget();

protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

private:
    int gridW;  //棋盘水平方向一个格子的宽度
    int gridH;  //棋盘水平方向一个格子的高度
    int startX; //棋盘起点x坐标
    int startY; //棋盘起点y坐标

    int chessX, chessY; //棋盘下标

};

#endif // CHESSWIDGET_H
