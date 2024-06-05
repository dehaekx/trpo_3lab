#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <QDir>
#include <QMap>
#include <QString>
#include <iostream>
#include <QFileInfo>
#include <QFileInfoList>

class CalculationStrategy
{
public:
    ~CalculationStrategy() = default;
    virtual QMap<QString, qint64> calculationMethod(const QString &path) const = 0;
};

class ByFolder_CalculationStrategy : public CalculationStrategy
{
public:
    ~ByFolder_CalculationStrategy() = default;
    virtual QMap<QString, qint64> calculationMethod(const QString &path)const override;

private:
    int CountFolder(const QString& path);
};

class ByFileType_CalculationStrategy : public CalculationStrategy
{
public:
    ~ByFileType_CalculationStrategy() = default;
    virtual QMap<QString, qint64> calculationMethod(const QString &path)const override;

private:
    void CountFileType(const QString &path, QMap<QString, qint64>& size);
};

#endif // CALCULATIONSTRATEGY_H
