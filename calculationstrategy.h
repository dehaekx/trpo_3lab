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

class Folder_CalculationStrategy : public CalculationStrategy
{
public:
    ~Folder_CalculationStrategy() = default;
    void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const override;

private:
    qint64 CountFolder(const QString& path) const;
};

class Type_CalculationStrategy : public CalculationStrategy
{
public:
    ~Type_CalculationStrategy() = default;
    void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const override;

private:
    void CountFileType(const QString &path, QMap<QString, qint64>& size) const;
};

#endif // CALCULATIONSTRATEGY_H
