#ifndef CONTEXT_H
#define CONTEXT_H
#include "calculationstrategy.h"
#include <memory>
#include <stdexcept>

class context
{
    QMap<QString, QString> map;

public:
    context(const std::shared_ptr<CalculationStrategy> & strategy);
    ~context() = default;

    void setStrategy(const std::shared_ptr<CalculationStrategy>& strategy);
    void f(const QString& size); // заполнить файл-размер
    const QMap<QString, qint64>& GetMap();
private:
    std::shared_ptr<CalculationStrategy> p;
};

#endif // CONTEXT_H
