#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "context.h"
#include "fileexplorermodel.h"
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected); // связываем левую часть экрана с обновлегрем данных в правой части
    void on_comboBoxSlot(const QString &str); // смена стратегии
signals:
    update(const QMap<QString, QString>* map_); // для обновлении мапы
public:
    MainWindow(QWidget *parent = nullptr, Context *context_ = nullptr);
    ~MainWindow();
private:
    FileExplorerModel *fileModel; // своя модель
    QFileSystemModel *dirModel;
    QTreeView *treeView; // • QTreeView - отображение данных в виде дерева (иерархического списка).
    QTableView *tableView; // • QTableView - отображение данных в виде таблицы;
    Context *context;
    QComboBox *comboBox;
};

#endif // MAINWINDOW_H
