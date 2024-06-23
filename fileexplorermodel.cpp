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
    if  (section == 0)
        return QString("NAME");
    else if (section == 1)
        return QString("PERCENT");
    return QVariant();
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || map.size() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole) || map.isEmpty())
    {
        return QVariant();
    }
    QMapIterator<QString, QString> i(map);
    // Перемещение итератора на нужную позицию
    int k = 0;
    i.next();
    while (i.hasNext() && k < index.row())
    {
        i.next();
        k++;
    }
    if (index.column() == 0)
    {
        return i.key();
    }
    else if (index.column() == 1)
    {
        return i.value();
    }
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
