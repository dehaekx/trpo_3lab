#include "context.h"


context::context(const std::shared_ptr<CalculationStrategy> &strategy)
{
    this->strategy_ = strategy;
}

void context::set_Strategy(const std::shared_ptr<CalculationStrategy>& strategy)
{
    this->strategy_ = strategy;
}

const QMap<QString, qint64> & context::get_Map()
{
    return map;
}

void context::f(const QString& size)
{
    this->strategy_->calculationMethod(size, map);
}
