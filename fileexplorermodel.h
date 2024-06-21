#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QFileSystemModel>
#include <QObject>
#include <QMap>

// QFileSystemModel – модель для работы с файлами и папками на локальном компьютере;

class FileExplorerModel: public QFileSystemModel
{
    Q_OBJECT
public:
    FileExplorerModel(QObject *parent = nullptr);
    // int rowCount();
    // int columnCount();
    // QVariant headerData();
    // QVariant setData();

};

#endif // FILEEXPLORERMODEL_H
