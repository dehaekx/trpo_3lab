#ifndef TYPE_STRATEGY_H
#define TYPE_STRATEGY_H
#include "calculationstrategy.h"

class Type_CalculationStrategy : public CalculationStrategy
{
public:
    ~Type_CalculationStrategy() = default;
    void calculationMethod(const QString &path, QMap<QString, qint64> &cont) const override;

private:
    void CountFileType(const QString &path, QMap<QString, qint64>& size) const;
};

#endif // TYPE_STRATEGY_H
