#include "calculationstrategy.h"

qint64 Folder_CalculationStrategy::CountFolder(const QString &path) const
{
    // QMap<QString, qint64> fileTypeSizes;
    // CountFileType(path, fileTypeSizes);
    // return fileTypeSizes;

    qint64 result = 0;

    // Make a checking for path is not emphty

    QDir direction = path;
    QFileInfoList fileInfo = direction.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = direction.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < folderInfo.size(); i++)
    {
        QFileInfo folderI = folderInfo.at(i);
        result += CountFolder(folderI.filePath());
    }
    for (int i = 0; i < folderInfo.size(); i++)
    {
        QFileInfo fileI = folderInfo.at(i);
        result += fileI.size();
    }
    return result;
}



void Folder_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    qint64 result = 0;

    // Make a checking for path is not emphty

    QDir directon = path;
    QFileInfoList fileInfo = directon.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = directon.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < fileInfo.size(); i++)
    {
        QFileInfo fileI = fileInfo.at(i);
        result += fileI.size();
    }
    cont.insert(QString("*Current path*"), result);
    for (int i = 0; i < folderInfo.size(); i++)
    {
        QFileInfo folderI = folderInfo.at(i);
        cont.insert(folderI.fileName(), CountFolder(folderI.filePath()));
    }
}

void Type_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    CountFileType(path, cont);
}

void Type_CalculationStrategy::CountFileType(const QString &path, QMap<QString, qint64>& size) const
{
    // Make a checking for path is not emphty

    QDir direction = path;
    QFileInfoList fileInfo = direction.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = direction.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < folderInfo.size(); i++) {
        QFileInfo folderI = folderInfo.at(i);
        CountFileType(folderI.filePath(), size);
    }
    for (int i = 0; i < fileInfo.size(); i++) {
        QFileInfo fileI = fileInfo.at(i);
        size[fileI.completeSuffix()] += fileI.size();
    }

}
