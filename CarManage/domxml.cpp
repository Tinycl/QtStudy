#include "domxml.h"
#include <QFile>
#include <QDomDocument> //文件
#include <QDomProcessingInstruction> //格式头部
#include <QDomElement>  //元素
#include <QTextStream> //文件流
#include <QDebug>
#include <QDateTime>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

DomXML::DomXML()
{

}

//创建xml空文件
void DomXML::createXML(QString filePath)
{
    QFile file(filePath); //关联文件名字
    if( true == file.exists() ) //如果存在不创建
    {
        cout << "文件已经存在";
        return;
    }
    else
    { //不存在才创建
        //只写方式打开文件
        bool isOk = file.open(QIODevice::WriteOnly);
        if(true == isOk)//如果打开成功
        {
            //创建xml文档对象
            QDomDocument doc;
            //创建xml头部格式 <?xml version='1.0' encoding='utf-8'?>
            QDomProcessingInstruction ins;
            ins = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'utf-8\'");
            //追加元素
            doc.appendChild(ins);

            //根节点元素
            QDomElement root = doc.createElement("日销售清单");
            doc.appendChild(root);

            //保存
            QTextStream stream(&file); //文本流关联文件
            doc.save(stream, 4); //4 缩进字符

            file.close(); //关闭文件

        }
        else
        {
            cout << "WriteOnly error";
            return;
        }
    }

}

void DomXML::appendXML(QString filePath, QStringList list)
{
    QFile file(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(true == isOk) //打开成功
    {
        //file和xml文档对象关联
        QDomDocument doc;
        isOk = doc.setContent(&file);
        if(isOk) //如果关联成功
        {
            file.close(); //关闭文件
            //获取根节点元素
            QDomElement root = doc.documentElement();

            //获取当前时间
            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd"); //2016-01-08

            //判断根节点下有没有子节点
            if( root.hasChildNodes() ) //如果有子节点
            {
                //查找最后一个子节点
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr)
                {//有有当天日期
                    //写有效数据
                    writeXML(doc, lastEmt, list);

                }
                else //如果没有
                {
                    //创建日期子节点元素
                    QDomElement dateEmt = doc.createElement("日期");
                    //创建date属性
                    QDomAttr dateAttr = doc.createAttribute("date");
                    //设置属性的值
                    dateAttr.setNodeValue(dateStr);
                    //节点和属性关联
                    dateEmt.setAttributeNode(dateAttr);

                    //把日期节点追加到根节点上
                    root.appendChild(dateEmt);

                    //写有效数据
                    writeXML(doc, dateEmt, list);
                }

            }
            else //没有子节点
            {
               //创建日期子节点元素
               QDomElement dateEmt = doc.createElement("日期");
               //创建date属性
               QDomAttr dateAttr = doc.createAttribute("date");
               //设置属性的值
               dateAttr.setNodeValue(dateStr);
               //节点和属性关联
               dateEmt.setAttributeNode(dateAttr);

               //把日期节点追加到根节点上
               root.appendChild(dateEmt);

               //写有效数据
               writeXML(doc, dateEmt, list);

            }

            //保存文件
            isOk = file.open(QIODevice::WriteOnly);
            if(isOk)
            {
                QTextStream stream(&file);
                doc.save(stream, 4);
                file.close();

            }

        }
        else
        {
            cout << "setContent error";
            return;
        }


    }
    else
    {
        cout << "ReadOnly error";
    }

}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    //获取当前时间
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("hh-mm-ss"); //16:05:22

    //创建时间节点元素
    QDomElement timeEmt = doc.createElement("时间");
    //创建属性
    QDomAttr timeAttr = doc.createAttribute("time");
    //给属性设置值
    timeAttr.setNodeValue(timeStr);
    //时间节点元素和属性关联
    timeEmt.setAttributeNode(timeAttr);
    //把时间节点追击到日期节点后面
    root.appendChild(timeEmt);

    QDomElement factory = doc.createElement("厂家");
    QDomElement brand = doc.createElement("品牌");
    QDomElement price = doc.createElement("报价");
    QDomElement num = doc.createElement("数量");
    QDomElement total = doc.createElement("金额");


    QDomText text = doc.createTextNode(list.at(0));
    factory.appendChild(text);

    text = doc.createTextNode(list.at(1));
    brand.appendChild(text);

    text = doc.createTextNode(list.at(2));
    price.appendChild(text);

    text = doc.createTextNode(list.at(3));
    num.appendChild(text);

    text = doc.createTextNode(list.at(4));
    total.appendChild(text);


    timeEmt.appendChild(factory);
    timeEmt.appendChild(brand);
    timeEmt.appendChild(price);
    timeEmt.appendChild(num);
    timeEmt.appendChild(total);

}

void DomXML::readXML(QString filePath, QStringList &fList, QStringList &bList, QStringList &pList, QStringList &nList, QStringList &tList)
{
    QFile file(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(true == isOk) //打开成功
    {
        //file和xml文档对象关联
        QDomDocument doc;
        isOk = doc.setContent(&file);

        if(isOk) //如果关联成功
        {
            //获取根节点
            QDomElement root = doc.documentElement();
            file.close();

            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd");


            if(root.hasChildNodes()) //有没有子节点
            {
                //找最后一个节点元素
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr)//判断有没有当天日期
                {
                    //找出当前日期下所有时间子节点
                    QDomNodeList list = lastEmt.childNodes();
                    for(int i = 0; i < list.size(); i++)
                    {
                        //list.at(0).toElement();
                        //转换为元素，找到时间节点下的所有子节点
                        QDomNodeList subList = list.at(i).toElement().childNodes();
                        //厂家
                        QString factory = subList.at(0).toElement().text();
                        fList.append(factory);

                        QString brand = subList.at(1).toElement().text();
                        bList.append(brand);

                        QString price = subList.at(2).toElement().text();
                        pList.append(price);

                        QString num = subList.at(3).toElement().text();
                        nList.append(num);

                        QString total = subList.at(4).toElement().text();
                        tList.append(total);
                    }


                }
                else
                {
                    cout << "没有当天日期";
                    return;
                }


            }
            else
            {
                cout << "没有子节点";
                return;
            }


        }
        else
        {
            cout << "setContent error";
            return;
        }
    }
    else
    {
        cout << "ReadOnly error";
        return;
    }

}
