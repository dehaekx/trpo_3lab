#include "fileexplorermodel.h"

FileExplorerModel::FileExplorerModel(QObject *parent, QMap<QString, QString> *map_): QAbstractItemModel(parent)
{
    map = *map_;
}

QModelIndex FileExplorerModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent))
    {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex FileExplorerModel::parent(const QModelIndex &child) const { Q_UNUSED(child) return QModelIndex(); }

int FileExplorerModel::rowCount(const QModelIndex &par) const{ Q_UNUSED(par) return map.size(); }

int FileExplorerModel::columnCount(const QModelIndex &par) const { Q_UNUSED(par) return 2;}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (orientation == Qt::Vertical)
    {
        return section;
    }
    switch (section)
    {
        case 0:
            return QString("NAME");
        case 1:
            return QString("PERCENT");
    }
    return QVariant();
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || map.size() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole) || map.isEmpty())
    {
        return QVariant();
    }
    // Получение списка ключей из карты
    QList<QString> keys = map.keys();

    // Проверка валидности индекса строки
    if (index.row() >= keys.size())
    {
        return QVariant();// если индекс строки больше или равен количеству ключей
    }

    // Получение ключа для текущей строки
    QString key = keys.at(index.row());

    // Возвращение ключа или значения в зависимости от колонки
    if (index.column() == 0)
    {
        return key;
    }
    else if (index.column() == 1)
    {
       return map.value(key);
    }

    return QVariant();
}

void FileExplorerModel::updmapSlot(const QMap<QString, QString>* map_)
{
    beginResetModel();  // помогла при выводе не все файлы выводились
    if(map_)
    {
        qDebug() << "SFDPODPOCKSPOCKSPODKCPOSKDCOPSKDCKSDPCOSD";
        map = *map_;
        //qDebug() << map;
    }
    endResetModel();
}
