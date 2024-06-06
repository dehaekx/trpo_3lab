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
    virtual void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const = 0;
};




class Folder_CalculationStrategy : public CalculationStrategy
{
public:
    ~Folder_CalculationStrategy() = default;
     void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const = 0;

private:
    qint64 CountFolder(const QString& path);
};





class Type_CalculationStrategy : public CalculationStrategy
{
public:
    ~Type_CalculationStrategy() = default;
     void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const = 0;

private:
    void CountFileType(const QString &path, QMap<QString, qint64>& size) const;
};

#endif // CALCULATIONSTRATEGY_H
