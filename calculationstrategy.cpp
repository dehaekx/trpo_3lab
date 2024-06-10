#include "calculationstrategy.h"

qint64 Folder_CalculationStrategy::CountFolder(const QString &path) const
{
    qint64 result = 0;
    // Make a checking for path is not emphty
    if (path.isEmpty() || !QFileInfo(path).isDir())
    {
        return result;
    }
    QDir directory(path);
    QFileInfoList fileInfolist = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfolist = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : fileInfolist)
    {
        result += fileInfo.size();
    }
    for (const QFileInfo &folderInfo : folderInfolist)
    {
        result += CountFolder(folderInfo.filePath());
    }
    return result;
}



void Folder_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    // Make a checking for path is not emphty
    QFileInfo pathinfo(path);
    if (!pathinfo.isDir())
    {
        return;
    }
    qint64 result = 0;
    QDir directory(path);
    QFileInfoList fileInfolist = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfolist = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : fileInfolist)
    {
        result += fileInfo.size();
    }
    cont.insert(QString("Current path"), result);
    for (const QFileInfo &folderInfo : folderInfolist)
    {
        cont.insert(folderInfo.fileName(), CountFolder(folderInfo.filePath()));
    }
}

void Type_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    CountFileType(path, cont);
}

void Type_CalculationStrategy::CountFileType(const QString &path, QMap<QString, qint64>& size) const
{
    // Проверка, что путь не пуст и является директорией
    if (path.isEmpty() || !QFileInfo(path).isDir())
    {
        return;
    }
    QDir directory(path);
    QFileInfoList fileInfolist = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfolist = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &folderInfo : folderInfolist)
    {
        CountFileType(folderInfo.filePath(), size);
    }
    for (const QFileInfo &fileInfo : fileInfolist)
    {
        size[fileInfo.completeSuffix()] += fileInfo.size();
    }
}
