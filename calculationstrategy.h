#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <QDir>
#include <QMap>
#include <QString>
#include <iostream>

class CalculationStrategy
{
public:
    ~CalculationStrategy() = default;
    virtual void calculationMethod(QMap<QString, int>& map, const QString& core) = 0;
};

class ByFolder_CalculationStrategy : public CalculationStrategy
{
public:
    ~ByFolder_CalculationStrategy() = default;
    void calculationMethod(QMap<QString, int>& map, const QString& core);
private:
    int CountDir(const QString& path);
};

class ByFileType_CalculationStrategy : public CalculationStrategy
{
public:
    ~ByFileType_CalculationStrategy() = default;
    void calculationMethod(QMap<QString, int>& map, const QString& core);
private:
    void CountFormat(const QString &path, QMap<QString, int>& memory);
};

#endif // CALCULATIONSTRATEGY_H
