#include "context.h"


context::context(const std::shared_ptr<CalculationStrategy> &strategy)
{
    p = strategy;
}

void context::setStrategy(const std::shared_ptr<CalculationStrategy>& strategy)
{
    p = strategy;
}

const QMap<QString, qint64> & context::GetMap()
{
    return map;
}

void context::f(const QString& size)
{
    p->calculationMethod(size, map);
}
