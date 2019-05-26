#ifndef PIE_H
#define PIE_H

#include <QWidget>
#include <QMap>

typedef struct SECTOR_INFO
{
    float percent;
    QColor color;
    QString description;
}SectorInfo;

class Pie : public QWidget
{
    Q_OBJECT
public:
    explicit Pie(QWidget *parent = 0);
    ~Pie();

    // 设置圆的直径
    void setDiameter(int diameter);
    void setTopLeft(QPoint pt);
    // 设置数据
    void setData(QVector<SectorInfo> map_data);

protected:
    void paintEvent(QPaintEvent *event);


private:
    QVector<SectorInfo> m_result;
    int m_diameter;
    QPoint m_topLeft;
};

#endif // PIE_H
