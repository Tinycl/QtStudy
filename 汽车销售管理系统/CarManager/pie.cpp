#include "pie.h"
#include <QPainter>
#include <QtCore/qmath.h>
#include <QVariant>
#include <QApplication>
#include <QDesktopWidget>

Pie::Pie(QWidget *parent) :
    QWidget(parent)
{
    m_diameter = 250;
    m_topLeft = QPoint(10, 10);
}

Pie::~Pie()
{
}

void Pie::setDiameter(int diameter)
{
    m_diameter = diameter;
}

void Pie::setTopLeft(QPoint pt)
{
    m_topLeft = pt;
}

void Pie::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    //反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    int left_x = m_topLeft.x();    // 左边界
    int top_y = m_topLeft.y();     // 上边界
    int rect_height = 20;   // 颜色图解矩形的高度
    int space_height = 15;  // 颜色图解矩形的宽度

    // 计算矩形显示的起始x坐标
    int rect_start_x = m_topLeft.x() + m_diameter + 25;
    // 计算矩形显示的起始x坐标
    int start_y = m_topLeft.y() + m_diameter / 2;
    //先画出颜色图解
    QVector<SectorInfo>::iterator it = m_result.begin();
    for(; it!=m_result.end(); ++it)
    {
        int rect_width = 30;
        int space_width = 10;
        painter.setBrush( (*it).color );

        painter.drawRect(rect_start_x, start_y, rect_width, rect_height);

        // 计算文本显示的起始x坐标
        int text_start_x = rect_start_x + space_width + rect_width;
        // 计算文本显示的起始y坐标
        //int text_start_y = m_topLeft.y() + m_diameter / 2 + i * (space_height + rect_height);
        painter.drawText( text_start_x, 13 + start_y, (*it).description );
        start_y += (rect_height + space_height);
    }
    painter.setPen( QPen(Qt::black, 1) );
    const int FULL_CIRCLE = 5760;
    const int RADIUS = 140;
    QRect rect(left_x, top_y, m_diameter, m_diameter);
    int count = 0;
    for(it=m_result.begin(); it!=m_result.end(); ++it)
    {
        count += (*it).percent;
    }
    //如果0，那就先画一个白色的圆形
    if( 0 == count )
    {
        painter.setBrush( Qt::white );
        painter.drawEllipse(rect);
        return;
    }

    int pos = 0;
    int angle;
    for(it=m_result.begin(); it!=m_result.end(); ++it)
    {
        if( 0 == (*it).percent )
            continue;
        painter.setBrush( (*it).color );
        double persent = (double)(*it).percent / count;
        angle = FULL_CIRCLE * persent;

        //画出各个对应的扇形
        double abc = 3.14 * 2 * (double)(pos + angle/2) / FULL_CIRCLE;
        double tx = 100 * qCos(abc) + left_x + RADIUS;
        double ty = -100 * qSin(abc) + top_y + RADIUS;
        painter.drawPie(rect, pos, angle);
        //在扇形上写注释（百分比）
        QString temp;
        temp.sprintf("%0.1lf%%", persent*100);
        painter.drawText(tx-20, ty, temp);
        pos += angle;
    }
}

void Pie::setData(QVector<SectorInfo> map_data)
{
    m_result = map_data;
    QVector<SectorInfo>::iterator it = m_result.begin();
    for(int i=0; it!=m_result.end(); ++it, ++i)
    {
        // 设置随机色
        (*it).color = QColor(qrand()%255, qrand()%255, qrand()%255);
    }
    // 窗口重绘
    update();
}

