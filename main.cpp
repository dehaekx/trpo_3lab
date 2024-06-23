#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QMap>
#include "context.h"
#include "folder_strategy.h"
#include "type_strategy.h"
#include "mainwindow.h"

void print_Map(const QMap<QString, qint64> &map);
void print_Map(const QMap<QString, QString> *map);
//QMap<QString, QString>* CountVolumePercent(const QMap<QString, qint64>& size, int strategy);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString currentReposiroty = QDir::currentPath().section("/", 0, -2);
    qDebug() << "Direction: " << currentReposiroty << Qt::endl;
    //qDebug() << currentReposiroty << Qt:: endl;
    QString info = currentReposiroty + "/tests";

    // /tests                  - не пустая + содержит вложения
    // /tests/test1_repository - содержит папки
    // /tests/test2_repository - пустая
    // /tests/test3_repository - не пустая, но с файлами, имеющие развер 0
    // /tests/test4_repository - содержит вложения

    // Использование контекста со стратегией Folder_CalculationStrategy
    // Context ctx(std::make_shared<Folder_CalculationStrategy>());
    // ctx.runStrategy(info);
    // qDebug() << "Folders:" << Qt::endl;
    // print_Map(ctx.get_Map());
    // qDebug() << "Folder Percentages:" << Qt::endl;
    // print_Map(ctx.CountVolumePercent(ctx.get_Map(), 1));

    // qDebug() << Qt::endl << "Change strategy" << Qt::endl;

    // Изменение стратегии на Type_CalculationStrategy
    // ctx.set_Strategy(std::make_shared<Type_CalculationStrategy>());
    // ctx.runStrategy(info);
    // qDebug() << "Types:" << Qt::endl;
    // print_Map(ctx.get_Map());
    // qDebug() << "Type Percentages:" << Qt::endl;
    // print_Map(ctx.CountVolumePercent(ctx.get_Map(), 2));

    Context ctx(std::make_shared<Folder_CalculationStrategy>());
    MainWindow w(0, &ctx);
    w.show();
    return a.exec();
}





void print_Map(const QMap<QString, qint64> &map)
{
    if (!map.isEmpty())
    {
        for (auto it = map.constBegin(); it != map.constEnd(); ++it)
        {
            qDebug() << it.key() << ": " << it.value() << Qt::endl;
        }
    }
}

void print_Map(const QMap<QString, QString> *map)
{
    if (map && !map->isEmpty())
    {
        for (auto it = map->constBegin(); it != map->constEnd(); ++it)
        {
            qDebug() << it.key() << ": " << it.value() << Qt::endl;
        }
    }
}





































// QMap<QString, QString>* CountVolumePercent(const QMap<QString, qint64>& cont, int strategy)
// {
//     float accuracy = 0.01;
//     // Инициализация переменных
//     float total = 0;
//     bool flag = false;
//     QMap<QString, QString>* map = new QMap<QString, QString>;
//     if (!map || cont.isEmpty())
//     {
//         return map;
//     }

//     // Подсчёт общего количества
//     for (auto value : cont)
//     {
//         total += value;
//     }

//     // Обработка данных в зависимости от типа
//     if (strategy == 2) // types
//     {
//         if (total == 0)
//         {
//             for (auto it = cont.constBegin(); it != cont.constEnd(); ++it)
//             {
//                 map->insert(QString(".") + it.key(), QString("0.00 %"));
//             }
//             return map;
//         }

//         float others = 0;
//         for (auto it = cont.constBegin(); it != cont.constEnd(); ++it)
//         {
//             float percent = it.value() / total;
//             if (percent < accuracy)
//             {
//                 others += percent;
//                 flag = true;
//             }
//             else
//             {
//                 map->insert(QString(".") + it.key(), QString::number(percent * 100, 'f', 2) + " %");
//             }
//         }
//         if (flag)
//         {
//             map->insert("Others", QString::number(others * 100, 'f', 2) + " %");
//         }
//     }
//     else if (strategy == 1) // folders
//     {
//         if (total == 0)
//         {
//             map->insert("Current path", "0.00 %");
//             return map;
//         }
//         for (auto it = cont.constBegin(); it != cont.constEnd(); ++it)
//         {
//             float percent = it.value() / total;
//             if (percent == 0)
//             {
//                 map->insert(it.key(), "0.00 %");
//             }
//             else if (percent < accuracy)
//             {
//                 map->insert(it.key(), QString("%1 %").arg(QString::number(accuracy)));
//             }
//             else
//             {
//                 map->insert(it.key(), QString("%1 %").arg(QString::number(percent * 100, 'f', 2)));
//             }
//         }
//     }

//     return map;
// }
