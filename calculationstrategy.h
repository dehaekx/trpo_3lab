#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <QDir>
#include <QMap>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>

/*
 * Интерфейс Стратегии объявляет операции, общие для всех поддерживаемых версий
 * некоторого алгоритма.
 *
 * Контекст использует этот интерфейс для вызова алгоритма, определённого
 * Конкретными Стратегиями.
 */
class CalculationStrategy
{
public:
    ~CalculationStrategy() = default;
    virtual void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const = 0;
};

#endif // CALCULATIONSTRATEGY_H
