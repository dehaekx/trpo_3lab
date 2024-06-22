#ifndef CONTEXT_H
#define CONTEXT_H
#include "calculationstrategy.h"
#include <memory>

class Context
{
private:
    std::shared_ptr<CalculationStrategy> strategy_;
    QMap<QString, qint64> map;
public:
    Context(const std::shared_ptr<CalculationStrategy> & strategy = nullptr);
    ~Context() = default;

    void set_Strategy(const std::shared_ptr<CalculationStrategy>& strategy);
    void runStrategy(const QString& path);
    const QMap<QString, qint64>& get_Map();

    QMap<QString, QString>* CountVolumePercent(const QMap<QString, qint64>& cont, int strategy, float accuracy = 0.01);
};

#endif // CONTEXT_H
