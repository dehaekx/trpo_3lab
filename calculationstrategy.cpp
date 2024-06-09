#include "calculationstrategy.h"

qint64 Folder_CalculationStrategy::CountFolder(const QString &path) const
{
    qint64 result = 0;

    // Make a checking for path is not emphty
    if (path.isEmpty())
    {
        return result;
    }
    if (!QFileInfo(path).isDir())
    {
        return result;
    }

    QDir direction = path;
    QFileInfoList fileInfo = direction.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = direction.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < folderInfo.size(); i++)
    {
        QFileInfo folder = folderInfo.at(i);
        result += CountFolder(folder.filePath());
    }
    for (int i = 0; i < fileInfo.size(); i++)
    {
        QFileInfo file = fileInfo.at(i);
        result += file.size();
    }
    return result;
}



void Folder_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    qint64 result = 0;

    // Make a checking for path is not emphty
    if (!QFileInfo(path).isDir())
    {
        return;
    }
    QDir directon = path;
    QFileInfoList fileInfo = directon.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = directon.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < fileInfo.size(); i++)
    {
        QFileInfo file = fileInfo.at(i);
        result += file.size();
    }
    cont.insert(QString("Current path"), result);

    for (int i = 0; i < folderInfo.size(); i++)
    {
        QFileInfo folder = folderInfo.at(i);
        cont.insert(folder.fileName(), CountFolder(folder.filePath()));
    }
}

void Type_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    CountFileType(path, cont);
}

void Type_CalculationStrategy::CountFileType(const QString &path, QMap<QString, qint64>& size) const
{
    // Make a checking for path is not emphty
    if(path.isEmpty())
    {
        return;
    }
    if(!QFileInfo(path).isDir())
    {
        return;
    }
    QDir direction = path;
    QFileInfoList fileInfo = direction.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = direction.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < folderInfo.size(); i++)
    {
        QFileInfo folder = folderInfo.at(i);
        CountFileType(folder.filePath(), size);
    }
    for (int i = 0; i < fileInfo.size(); i++)
    {
        QFileInfo file = fileInfo.at(i);
        size[file.completeSuffix()] += file.size();
    }

}
