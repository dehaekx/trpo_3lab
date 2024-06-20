#include "mainwindow.h"

#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : //QWidget(parent)
    QMainWindow(parent)
{
    //Устанавливаем размер главного окна
    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Choosen Path: ");
    QString homePath = QDir::homePath();

    // Создаем и настраиваем модель файловой системы для директорий
    // Определим  файловой системы:
    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath); // Устанавливаем корневой путь модели

    // Создаем и настраиваем модель файловой системы для файлов
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(homePath);

    //Показать как дерево, пользуясь готовым видом:

    // Создаем виджет дерева и устанавливаем модель директорий
    treeView = new QTreeView();
    treeView->setModel(dirModel); // Устанавливаем модель дерева
    treeView->expandAll(); // Раскрываем все узлы дерева

    // Создаем QSplitter для разделения окна на две части // для разделения представлений
    QSplitter *splitter = new QSplitter(parent);

    // Создаем таблицу и устанавливаем модель файлов
    tableView = new QTableView;
    tableView->setModel(fileModel); // Устанавливаем модель таблицы

    // Добавляем дерево и таблицу в QSplitter
    splitter->addWidget(treeView);
    splitter->addWidget(tableView);
    setCentralWidget(splitter); // Устанавливаем QSplitter в качестве центрального виджета главного окна

    QItemSelectionModel *selectionModel = treeView->selectionModel(); // Получаем модель выбора для дерева
    QModelIndex rootIx = dirModel->index(0, 0, QModelIndex()); // Получаем корневой индекс модели директорий //корневой элемент

    QModelIndex indexHomePath = dirModel->index(homePath); // Получаем индекс домашнего каталога
    QFileInfo fileInfo = dirModel->fileInfo(indexHomePath); // Получаем информацию о файле (или директории) по индексу

    /* Рассмотрим способы обхода содержимого папок на диске.
     * Предлагается вариант решения, которы может быть применен для более сложных задач.
     * Итак, если требуется выполнить анализ содержимого папки, то необходимо организовать обход содержимого. Обход выполняем относительно модельного индекса.
     * Например:*/
    if (fileInfo.isDir()) {
        /*
         * Если fileInfo папка то заходим в нее, что бы просмотреть находящиеся в ней файлы.
         * Если нужно просмотреть все файлы, включая все вложенные папки, то нужно организовать рекурсивный обход.
        */
        QDir dir  = fileInfo.dir();

        if (dir.cd(fileInfo.fileName())) {
            /**
             * Если зашли в папку, то пройдемся по контейнеру QFileInfoList ,полученного методом entryInfoList,
             * */

            foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type)) {
                qDebug() << inf.fileName() << "---" << inf.size();
            }

            dir.cdUp();//выходим из папки
        }
    }

    // Перебираем все файлы и директории в текущем QDir и выводим их имена и размеры
    QDir dir = fileInfo.dir();
    foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Type)) {

        qDebug() << inf.fileName() << "---" << inf.size();
    }



    treeView->header()->resizeSection(0, 200); // Устанавливаем размер первого столбца в дереве

    // Подключаем сигнал изменения выбора к слоту on_selectionChangedSlot
    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

    //Пример организации установки курсора в TreeView относит ельно модельного индекса
    QItemSelection toggleSelection;
    QModelIndex topLeft;
    topLeft = dirModel->index(homePath);  // Получаем индекс домашнего каталога
    dirModel->setRootPath(homePath); // Устанавливаем корневой путь модели

    // Выделяем элемент в дереве
    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}
//Слот для обработки выбора элемента в TreeView
//выбор осуществляется с помощью курсора

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QModelIndex index = treeView->selectionModel()->currentIndex(); // Получаем текущий индекс выбора в дереве

    // Получаем список выбранных индексов
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    // Если выбрано хотя бы одно, обновляем строку состояния
    if (indexs.count() >= 1)
    {
        QModelIndex ix =  indexs.constFirst(); // Получаем первый выбранный индекс
        filePath = dirModel->filePath(ix);  // Получаем путь к файлу
        this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst())); // Обновляем сообщение строки состояния
    }

    //TODO: !!!!!
    /*
    Тут простейшая обработка ширины первого столбца относительно длины названия папки.
    Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
    Требуется доработка(переработка).
    */

    // Обработка ширины первого столбца в зависимости от длины имени папки
    int length = 200;
    int dx = 30;

    // Увеличиваем длину столбца, если имя папки длинное
    if (dirModel->fileName(index).length() * dx > length)
    {
        length = length + dirModel->fileName(index).length() * dx;
        qDebug() << "r = " << index.row() << "c = " << index.column() << dirModel->fileName(index) << dirModel->fileInfo(
                                                                                                                  index).size();

    }

    // Изменяем размер первого столбца в дереве
    treeView->header()->resizeSection(index.column(), length + dirModel->fileName(index).length());
    // Обновляем корневой индекс таблицы для отображения файлов в выбранной директории
    tableView->setRootIndex(fileModel->setRootPath(filePath));
}

MainWindow::~MainWindow()
{

}
