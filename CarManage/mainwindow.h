#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDB(); //连接数据库
    void initData(); //初始化

private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_comboBoxFactory_currentIndexChanged(const QString &arg1);

    void on_comboBoxBrand_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_buttonCancel_clicked();

    void on_buttonSure_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
