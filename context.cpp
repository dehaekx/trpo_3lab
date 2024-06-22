#include "context.h"


Context::Context(const std::shared_ptr<CalculationStrategy> &strategy)
{
    if (strategy != nullptr)
    {
        this->strategy_ = strategy;
    }
    else
    {
        throw std::runtime_error("ERROR strategy is nullptr");
    }
}

void Context::set_Strategy(const std::shared_ptr<CalculationStrategy>& strategy)
{
    if (strategy != nullptr)
    {
        this->strategy_ = strategy;
    }
}

const QMap<QString, qint64> & Context::get_Map()
{
    return map;
}

void Context::runStrategy(const QString& path)
{
    this->strategy_->calculationMethod(path, map);
}


QMap<QString, QString>* Context::CountVolumePercent(const QMap<QString, qint64>& cont, int strategy, float accuracy)
{
    // Инициализация переменных
    float total = 0;
    bool flag = false;
    QMap<QString, QString>* map = new QMap<QString, QString>;
    if (!map || cont.isEmpty())
    {
        return map;
    }

    // Подсчёт общего количества
    for (auto value : cont)
    {
        total += value;
    }

    // Обработка данных в зависимости от типа
    if (strategy == 2) // types
    {
        if (total == 0)
        {
            for (auto it = cont.constBegin(); it != cont.constEnd(); ++it)
            {
                map->insert(QString(".") + it.key(), QString("0.00 %"));
            }
            return map;
        }

        float others = 0;
        for (auto it = cont.constBegin(); it != cont.constEnd(); ++it)
        {
            float percent = it.value() / total;
            if (percent < accuracy)
            {
                others += percent;
                flag = true;
            }
            else
            {
                map->insert(QString(".") + it.key(), QString::number(percent * 100, 'f', 2) + " %");
            }
        }
        if (flag)
        {
            map->insert("Others", QString::number(others * 100, 'f', 2) + " %");
        }
    }
    else if (strategy == 1) // folders
    {
        if (total == 0)
        {
            map->insert("Current path", "0.00 %");
            return map;
        }
        for (auto it = cont.constBegin(); it != cont.constEnd(); ++it)
        {
            float percent = it.value() / total;
            if (percent == 0)
            {
                map->insert(it.key(), "0.00 %");
            }
            else if (percent < accuracy)
            {
                map->insert(it.key(), QString("%1 %").arg(QString::number(accuracy)));
            }
            else
            {
                map->insert(it.key(), QString("%1 %").arg(QString::number(percent * 100, 'f', 2)));
            }
        }
    }

    return map;
}
