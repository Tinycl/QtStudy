#include "carmanager.h"
#include "ui_carmanager.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSqlRecord>
#include <QDebug>

CarManager::CarManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarManager)
{
    ui->setupUi(this);

    this->setMinimumSize(900, 550);

    ui->toolBox->setCurrentIndex(0);

    // 创建空xml
    createXML();
    // 连接数据库
    bool bl = connectDB();
    if(!bl)
    {
        return;
    }

    // 销售车辆
    initSaleCar();

    // 统计
    initTongji();

    // 新车
    initNewCar();

    ui->title->setText("<center><h1>车辆管理</h1></center>");
    ui->stackedWidget->setCurrentIndex(0);
    // 车辆管理
    connect(ui->actionCar, &QAction::triggered, [=]()
    {
        // 车辆管理
       ui->stackedWidget->setCurrentIndex(0);
       ui->title->setText("<center><h1>车辆管理</h1></center>");
    });

    // 销售统计
    connect(ui->actionSale, &QAction::triggered, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->tongji);
        ui->title->setText("<center><h1>销售统计</h1></center>");
    });
}

CarManager::~CarManager()
{
    delete ui;
}

// 连接数据库
bool CarManager::connectDB()
{
    // 添加连接
    m_db = QSqlDatabase::addDatabase("QMYSQL" );
    // 连接设置
    m_db.setHostName("localhost");
    m_db.setDatabaseName("car");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    // 打开数据库
    if(!m_db.open())
    {
        QMessageBox::critical(this, "Error", m_db.lastError().text());
        return false;
    }
    return true;
}

void CarManager::initSaleCar()
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery("select name from factory");
    // 厂家
    ui->factory->setModel(model);
    ui->changjia->setModel(model);
    factoryChanged("请选择厂家");


    // qt4
    //connect(ui->factory, SIGNAL(currentIndexChanged(QString)), this, SLOT(factoryChanged(QString)));

    void (QComboBox::* sigItemChanged)(const QString &) = &QComboBox::currentIndexChanged;
    connect(ui->factory, sigItemChanged, this, &CarManager::factoryChanged);    // 厂家
    connect(ui->brand, sigItemChanged, this, &CarManager::brandChanged);    // 品牌
    void (QSpinBox::* sigValueChanged)(int) = &QSpinBox::valueChanged;
    connect(ui->number, sigValueChanged, [=](int value)
    {
        if(value == 0)
        {
            ui->ok->setEnabled(false);
            ui->sum->clear();
            ui->sum->setEnabled(false);
        }
        else
        {
            ui->ok->setEnabled(true);
            int sum = ui->price->text().toInt() * value;
            ui->sum->setText(QString::number(sum));
        }
    });

    // 确定
    connect(ui->ok, &QPushButton::clicked, [=]()
    {
        // 准备数据
        QString factory = ui->factory->currentText();
        QString brand = ui->brand->currentText();
        int number = ui->number->value();   // 销售数量
        int last = ui->last_num->text().toInt() - number;   // 卖完之后剩余的数量

        QSqlQuery query;
        QString sql = QString("select sell from brand where factory='%1' and name ='%2'").arg(factory).arg(brand);
        query.exec(sql);
        if(query.next())
        {
            int sell = query.value(0).toInt() + number;
            // 更新数据库
            QSqlDatabase::database().transaction(); // 记录更新前的状态
            sql = QString("update brand set sell=%1, last=%2 where factory='%3' and name='%4'")
                    .arg(sell).arg(last).arg(factory).arg(brand);
            bool bl = query.exec(sql);

            if(bl)
            {
                QSqlDatabase::database().commit();  // 提交
                // 销售数据写入到文件 xml
                writeXMLData();
                // 显示销售数据
                showDailyList();
            }
            else
            {
                // 状态回滚
                QSqlDatabase::database().rollback();
            }

        }

        // 初始化界面
        ui->factory->setCurrentText("请选择厂家");
    });

    // 取消
    connect(ui->cancle, &QPushButton::clicked, [=]()
    {
        ui->factory->setCurrentText("请选择厂家");
    });
}

void CarManager::factoryChanged(const QString &name)
{
    // 初始化
    ui->brand->clear();
    if(name == "请选择厂家")
    {
        ui->price->clear();
        ui->number->setValue(0);
        ui->last_num->clear();
        ui->sum->clear();
        ui->sum->setEnabled(false);
        ui->ok->setEnabled(false);
    }
    else
    {
        // 查数据库
        QSqlQuery query;
        query.exec(QString("select name from brand where factory='%1'").arg(name));

        while(query.next())
        {
            QString name = query.value(0).toString();
            ui->brand->addItem(name);
        }
    }
}

void CarManager::brandChanged(const QString &name)
{
    QSqlQuery query;

    QString sql = QString("select price, last from brand where factory = '%1' and name ='%2'")
            .arg(  ui->factory->currentText() )
            .arg( name );


    query.exec(sql);
    while(query.next())
    {

        int price = query.value(0).toInt();
        int last = query.value(1).toInt();
        ui->price->setText(QString::number(price));
        ui->last_num->setText(QString::number(last));
    }
}

void CarManager::createXML()
{
    QFile file("saleList.xml");
    bool bl = file.open(QIODevice::ReadOnly);
    if(bl)
    {
        return;
    }
    else
    {
        // 没有, 创建新文件
        file.open(QIODevice::WriteOnly);
        // xml文档对象
        QDomDocument doc;
        // 添加文件头
        QDomProcessingInstruction ins = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
        doc.appendChild(ins);

        // 添加根节点
        QDomElement root = doc.createElement("日销售清单");
        doc.appendChild(root);

        QTextStream stream(&file);
        // 将文档对象中的内容保存到文件中
        doc.save(stream, 4);
        file.close();
    }
}

void CarManager::writeXMLData()
{
    // 读文件 xml
    if(readXML())
    {
        QString curDate = getDateTime(Date);
        // 取出根节点
        QDomElement root = m_doc.documentElement();
        // 判断根节点有没有子节点
        if(!root.hasChildNodes())
        {
            // 没有孩子节点(日期节点)
            // 添加日期节点
            QDomElement dateElem = m_doc.createElement("日期");   // 创建节点
            QDomAttr attrDate = m_doc.createAttribute("date");     // 创建属性
            attrDate.setValue(curDate); // 设置属性的值
            dateElem.setAttributeNode(attrDate);
            // 日期节点添加到子节点下边
            root.appendChild(dateElem);
            // 添加汽车销售信息
            createNodes(dateElem);
        }
        else
        {
            // 有日期节点
            // 取到最后一个日期节点
            QDomElement lastElem = root.lastChildElement();
            // 将日期节点中日期取出来, 跟当天日期比较
            if(lastElem.attribute("date") == curDate)
            {
                // 有当天的日期
                // 直接添加卖车信息
                createNodes(lastElem);
            }
            else
            {
                // 添加日期节点
                QDomElement dateElem = m_doc.createElement("日期");   // 创建节点
                QDomAttr attrDate = m_doc.createAttribute("date");     // 创建属性
                attrDate.setValue(curDate); // 设置属性的值
                dateElem.setAttributeNode(attrDate);
                // 日期节点添加到子节点下边
                root.appendChild(dateElem);
                // 添加汽车销售信息
                createNodes(dateElem);
            }

        }
        // 将内存数据写入文件
        writeXML();
    }
}

bool CarManager::readXML()
{
    QFile file("saleList.xml");
    if(file.open(QIODevice::ReadOnly))
    {
        // 设置内容 - io对象的内容
        bool bl = m_doc.setContent(&file);
        if(bl)
        {
            file.close();
            return true;
        }
        file.close();
        return false;
    }
    else
    {
        return false;
    }
}

bool CarManager::writeXML()
{
    QFile file("saleList.xml");
    bool bl = file.open(QIODevice::WriteOnly);
    if(!bl)
    {
        return false;
    }
    QTextStream stream(&file);
    m_doc.save(stream, 4);
    file.close();
    return true;
}

QString CarManager::getDateTime(DateTimeType type)
{
    QDateTime dt = QDateTime::currentDateTime();
    if(type == Date)
    {
        return dt.toString("yyyy-MM-dd");
    }
    else if(type == Time)
    {
        return dt.toString("hh:mm:sss");
    }
    else
    {
        return dt.toString("yyyy-MM-dd hh:mm:ss");
    }

}

void CarManager::createNodes(QDomElement &parent)
{
    // 汽车销售信息节点
    QDomElement timeElem = m_doc.createElement("时间");
    QDomAttr arrtTime = m_doc.createAttribute("time");
    arrtTime.setValue(getDateTime(Time));
    timeElem.setAttributeNode(arrtTime);
    // 时间节点挂到日期节点下边
    parent.appendChild(timeElem);
    // 厂家
    QDomElement factoryElem = m_doc.createElement("厂家");
    // 品牌
    QDomElement brandElem = m_doc.createElement("品牌");
    // 报价
    QDomElement priceElem = m_doc.createElement("报价");
    // 数量
    QDomElement numberElem = m_doc.createElement("数量");
    // 金额
    QDomElement sumElem = m_doc.createElement("金额");

    // 创建文本节点
    QDomText text = m_doc.createTextNode(ui->factory->currentText());
    factoryElem.appendChild(text);
    text = m_doc.createTextNode(ui->brand->currentText());
    brandElem.appendChild(text);
    text = m_doc.createTextNode(ui->price->text());
    priceElem.appendChild(text);
    text = m_doc.createTextNode(ui->number->text());
    numberElem.appendChild(text);
    text = m_doc.createTextNode(ui->sum->text());
    sumElem.appendChild(text);

    // 添加到time节点下边
    timeElem.appendChild(factoryElem);
    timeElem.appendChild(brandElem);
    timeElem.appendChild(priceElem);
    timeElem.appendChild(numberElem);
    timeElem.appendChild(sumElem);
}

void CarManager::showDailyList()
{
    // 读xml
    if(readXML())
    {
        ui->listWidget->clear();
        // 拿出根节点
        QDomElement root = m_doc.documentElement();
        QString title = QString("************** %1 **************").arg(root.tagName());
        QListWidgetItem* item = new QListWidgetItem(title);
        item->setTextAlignment(Qt::AlignCenter);
        ui->listWidget->addItem(item);
        // 是否有子节点
        if(root.hasChildNodes())
        {
            // 找到最后一个日期节点
            QDomElement lastElem = root.lastChildElement();
            ui->listWidget->addItem(lastElem.attribute("date"));
            ui->listWidget->addItem(" ");
            // 有子节点
            // 最后一个的日期月当天日期比较
            if(lastElem.attribute("date") == getDateTime(Date))
            {
                // 当天有销售记录
                QDomNodeList nodeList = lastElem.childNodes();
                for(int i=0; i<nodeList.count(); ++i)
                {
                    QDomElement time = nodeList.at(i).toElement();
                    QDomNodeList subList = time.childNodes();
                    QString factory = subList.at(0).toElement().text();
                    QString brand = subList.at(1).toElement().text();
                    QString price = subList.at(2).toElement().text();
                    QString number = subList.at(3).toElement().text();
                    QString sum = subList.at(4).toElement().text();

                    QString str = QString("%1 卖出了 %2 - %3，单价： %4， 数量： %5， 总价： %6")
                            .arg(time.attribute("time")).arg(factory).arg(brand).arg(price)
                            .arg(number).arg(sum);
                    ui->listWidget->addItem(str);
                }
            }
        }
    }
}

void CarManager::initTongji()
{
    ui->wg_histgram->SetMaxValue(70);
    void (QComboBox::* sigItemChanged)(const QString &) = &QComboBox::currentIndexChanged;
    connect(ui->changjia, sigItemChanged, [=](const QString & name)
    {
        ui->pinpai->clear();
        ui->wg_histgram->Clear();
        QSqlQuery query;
        query.exec(QString("select name, sell from brand where factory = '%1'").arg(name));
        while(query.next())
        {
            QString name = query.value(0).toString();
            int sell = query.value(1).toInt();
            ui->pinpai->addItem(name);
            QColor color(qrand()%255, qrand()%255, qrand()%255);
            ui->wg_histgram->AddItem(name, sell, color);
            //ui->wg_histgram->update();
        }
    });

    // pinpai
    connect(ui->pinpai, sigItemChanged, [=](const QString &name)
    {
        QSqlQuery query;
        QVector<SectorInfo> vc;
        query.exec(QString("select sell, last from brand where factory='%1' and name ='%2'")
                   .arg(ui->changjia->currentText()).arg(name));
        if(query.next())
        {
            SectorInfo info;
            float sell = query.value(0).toInt();
            float last = query.value(1).toInt();
            float sum = sell + last;
            info.description = "已出售";
            info.percent = sell/sum*100;
            vc.push_back(info);
            info.description = "剩余";
            info.percent = 100 - info.percent;
            vc.push_back(info);
        }
        ui->wg_pie->setData(vc);
    });
}

void CarManager::initNewCar()
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("brand");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //

    ui->tableView->setModel(model);

    connect(ui->add, &QPushButton::clicked, [=]()
    {
        // 在model中添加新纪录
        QSqlRecord record = model->record();    // 获取model中的空记录
        // 获取model的行数
        int rows = model->rowCount();
        model->insertRecord(rows, record);

    });

    connect(ui->del, &QPushButton::clicked, [=]()
    {
        QItemSelectionModel* selectModel = ui->tableView->selectionModel();
        QModelIndexList modelList = selectModel->selectedRows(1);
        for(int i=0; i<modelList.size(); ++i)
        {
            model->removeRow(modelList.at(i).row());
        }
    });

    connect(ui->submit, &QPushButton::clicked, [=]()
    {
        model->submitAll();
    });

    connect(ui->revert, &QPushButton::clicked, [=]()
    {
        model->revertAll();
//        model->select();
        model->submitAll();
    });
}

void CarManager::on_toolBox_currentChanged(int index)
{
    if(0 == index)
    {
        ui->listWidget->show();
    }
    else
    {
        ui->listWidget->hide();
    }
}
