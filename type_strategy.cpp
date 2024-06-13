#include "type_strategy.h"

void Type_CalculationStrategy::calculationMethod(const QString &path, QMap<QString, qint64> &cont) const
{
    CountFileType(path, cont);
}

void Type_CalculationStrategy::CountFileType(const QString &path, QMap<QString, qint64>& cont) const
{
    // Проверка, что путь не пуст или не является директорией
    if (path.isEmpty() || !QFileInfo(path).isDir())
    {
        return;
    }
    QDir directory(path);
    QFileInfoList fileInfolist = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfolist = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &folderInfo : folderInfolist)
    {
        CountFileType(folderInfo.filePath(), cont);
    }
    for (const QFileInfo &fileInfo : fileInfolist)
    {
        cont[fileInfo.completeSuffix()] += fileInfo.size();
    }
}

