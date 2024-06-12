#ifndef FOLDER_STRATEGY_H
#define FOLDER_STRATEGY_H
#include "calculationstrategy.h"

class Folder_CalculationStrategy : public CalculationStrategy
{
public:
    ~Folder_CalculationStrategy() = default;
    void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const override;

private:
    qint64 CountFolder(const QString& path) const;
};

#endif // FOLDER_STRATEGY_H
