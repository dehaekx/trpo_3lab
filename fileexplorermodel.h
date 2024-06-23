#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QFileSystemModel>
#include <QObject>
#include <QMap>
#include <QDebug>

// QFileSystemModel – модель для работы с файлами и папками на локальном компьютере;

class FileExplorerModel: public QAbstractItemModel
{
    Q_OBJECT
public slots:
    void updmapSlot(const QMap<QString, QString>* map_);
public:
    FileExplorerModel(QObject *parent = nullptr, QMap<QString, QString>* map_ = nullptr);
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int rool) const override;
private:
    QMap<QString, QString> map;
};

#endif // FILEEXPLORERMODEL_H
