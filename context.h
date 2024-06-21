#ifndef CONTEXT_H
#define CONTEXT_H
#include "calculationstrategy.h"
#include <memory>

class context
{
private:
    std::shared_ptr<CalculationStrategy> strategy_;
    QMap<QString, qint64> map;
public:
    context(const std::shared_ptr<CalculationStrategy> & strategy = nullptr);
    ~context() = default;

    void set_Strategy(const std::shared_ptr<CalculationStrategy>& strategy);
    void runStrategy(const QString& path); // заполнить файл и его размер
    const QMap<QString, qint64>& get_Map();

    QMap<QString, QString>* CountVolumePercent(const QMap<QString, qint64>& cont, int strategy, float accuracy = 0.01);
};

#endif // CONTEXT_H
