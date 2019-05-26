#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDomDocument>
#include <QComboBox>
#include <QSqlTableModel>

namespace Ui {
class CarManager;
}

class CarManager : public QMainWindow
{
    Q_OBJECT

public:
    enum DateTimeType{Date, Time, DateTime};
    explicit CarManager(QWidget *parent = 0);
    ~CarManager();

    bool connectDB();
    // 出售车辆界面初始化
    void initSaleCar();
    // 创建xml文件(空的)
    void createXML();
    // 写数据到xml文件(内存中的操作, 写到了doc对象中)
    void writeXMLData();
    // 销售记录（读xml文件数据）
    void showDailyList();
    // 初始化统计界面
    void initTongji();
    // 初始化新车入库
    void initNewCar();

    // 从磁盘中读数据
    bool readXML();
    // 将数据写到磁盘中
    bool writeXML();
    // 获取时间
    QString getDateTime(DateTimeType type);
    void createNodes(QDomElement & parent);

public slots:
    void factoryChanged(const QString & name);
    void brandChanged(const QString &name);

private slots:
    void on_toolBox_currentChanged(int index);

private:
    Ui::CarManager *ui;
    QSqlDatabase m_db;
    QDomDocument m_doc;
};

#endif // CARMANAGER_H
