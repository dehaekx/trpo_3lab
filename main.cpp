#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QMap>
#include <QMapIterator>
#include "context.h"

void print_Map(const QMap<QString, qint64> map)
{
    if(!map.empty())
    {
        QMapIterator<QString, qint64> i(map);
        while(i.hasNext())
        {
            i.next();
            qDebug() << i.key() << QString(" - SIZE: ") << QString::number(i.value()) << Qt::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString currentReposiroty = QDir::currentPath().section("/", 0, -2);
    qDebug() << "Direction: " << currentReposiroty << Qt::endl;
    //qDebug() << currentReposiroty << Qt:: endl;
    QString info = currentReposiroty + "/tests";



    context context(std::make_shared<Folder_CalculationStrategy>());
    context.f(info);
    print_Map(context.get_Map());









    return a.exec();
}
