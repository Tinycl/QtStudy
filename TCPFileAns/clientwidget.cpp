#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    isStart = true;

    ui->progressBar->setValue(0); //当前值

    setWindowTitle("客户端");

    connect(tcpSocket, &QTcpSocket::connected,
    [=]()
    {
        //提示连接成功
        ui->textEdit->clear();
        ui->textEdit->append("和服务器连接成功，等待服务器传送文件……");
    }
    );

    connect(tcpSocket, &QTcpSocket::readyRead,
    [=]()
    {
        //取出接收的内容
        QByteArray buf = tcpSocket->readAll();

        if(true == isStart)
        {//接收头
            isStart = false;
            //解析头部信息 QString buf = "hello##1024"
            //                    QString str = "hello##1024#mike";
            //                            str.section("##", 0, 0)

            //初始化
            //文件名
            fileName = QString(buf).section("##", 0, 0);
            //文件大小
            fileSize = QString(buf).section("##", 1, 1).toInt();
            recvSize = 0;   //已经接收文件大小

            //打开文件
            //关联文件名字
            file.setFileName(fileName);

            //只写方式方式，打开文件
            bool isOk = file.open(QIODevice::WriteOnly);
            if(false == isOk)
            {
                qDebug() << "WriteOnly error 49";

                tcpSocket->disconnectFromHost(); //断开连接
                tcpSocket->close(); //关闭套接字

                return; //如果打开文件失败，中断函数
            }

            //弹出对话框，显示接收文件的信息
            QString str = QString("接收的文件: [%1: %2kb]").arg(fileName).arg(fileSize/1024);
            //QMessageBox::information(this, "文件信息", str);
            ui->textEdit->append(str);
            ui->textEdit->append("正在接收文件……");

            //设置进度条
            ui->progressBar->setMinimum(0); //最小值
            ui->progressBar->setMaximum(fileSize/1024); //最大值
            ui->progressBar->setValue(0); //当前值

        }
        else //文件信息
        {
            qint64 len = file.write(buf);
            if(len >0) //接收数据大于0
            {
                recvSize += len; //累计接收大小
                qDebug() << len;
            }

            //更新进度条
            ui->progressBar->setValue(recvSize/1024);

            if(recvSize == fileSize) //文件接收完毕
            {

                //先给服务发送(接收文件完成的信息)
                tcpSocket->write("file done");

                ui->textEdit->append("文件接收完成");
                QMessageBox::information(this, "完成", "文件接收完成");
                file.close(); //关闭文件
                //断开连接
                tcpSocket->disconnectFromHost();
                tcpSocket->close();

            }
        }

        }

    );


}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器的ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器连接
    tcpSocket->connectToHost(QHostAddress(ip), port);

    isStart = true;

    //设置进度条
    ui->progressBar->setValue(0);
}
