#ifndef DOMXML_H
#define DOMXML_H
#include <QString>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>


class DomXML
{
public:
    DomXML();

    static void createXML(QString filePath); //创建xml空文件
    //list.at(0) = 二汽神龙
    static void appendXML(QString filePath, QStringList list);
    static void writeXML(QDomDocument &doc, QDomElement &root, QStringList &list);

    static void readXML(QString filePath,
                        QStringList &fList,
                        QStringList &bList,
                        QStringList &pList,
                        QStringList &nList,
                        QStringList &tList

                        );

};

#endif // DOMXML_H
