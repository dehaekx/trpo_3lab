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

MainWindow::MainWindow(QWidget *parent, Context *context_)
    : //QWidget(parent)
    QMainWindow(parent)
{
    context = context_;
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

    // Создаем и настраиваем модель файловой системы для файлов // ЭТУ МОДЕЛЬ НУЖНО СДЕЛАТЬ
    fileModel = new FileExplorerModel(this, context->CountVolumePercent(context->get_Map(), 1));

    // Для выпадающего списка выбора стратегии:
    comboBox = new QComboBox(parent);
    comboBox->addItem("Folders strategy");
    comboBox->addItem("Type strategy");
    comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    treeView = new QTreeView();
    treeView->setModel(dirModel); // Устанавливаем модель дерева
    treeView->expandAll(); // Раскрываем все директории

    // Создаем таблицу и устанавливаем модель файлов
    tableView = new QTableView;
    tableView->setModel(fileModel); // Устанавливаем модель таблицы

    // Создаем QSplitter для разделения окна на две части // для разделения представлений
    QSplitter *splitter = new QSplitter(parent);
    // Добавляем дерево и таблицу в QSplitter
    splitter->addWidget(treeView);
    splitter->addWidget(tableView);
    //setCentralWidget(splitter); // Устанавливаем QSplitter в качестве центрального виджета главного окна

    QSplitter *splitter_v = new QSplitter(Qt::Vertical, parent);
    splitter_v->addWidget(comboBox);
    splitter_v->addWidget(splitter);

    setCentralWidget(splitter_v);



    QItemSelectionModel *selectionModel = treeView->selectionModel(); // Получаем модель выбора для дерева, следит при клике, что я выбираю

    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents); // Устанавливаем размер первого столбца в дереве
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // Подключаем сигнал изменения выбора к слоту on_selectionChangedSlot
    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView

    // связть между левой частью и правой
    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);
    // левую часть и правой qmap обновляем
    QObject::connect(this, &MainWindow::update, fileModel, &FileExplorerModel::updmapSlot);
    // смене стратегии
    QObject::connect(comboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_comboBoxSlot);

    //Пример организации установки курсора в TreeView относительно модельного индекса
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

// связывает курсор с моделью
void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    // Получаем список выбранных индексов
    QModelIndexList indexs = selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    // Если выбрано хотя бы одно, обновляем строку состояния
    if (indexs.count() >= 1)
    {
        QModelIndex ix =  indexs.constFirst(); // Получаем первый выбранный индекс
        filePath = dirModel->filePath(ix);  // Получаем путь к файлу
        this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst())); // Обновляем сообщение строки состояния
        context->runStrategy(dirModel->filePath(indexs.constFirst())); // путь считает правильно
        //qDebug() << dirModel->filePath(indexs.constFirst()) << Qt::endl;
        emit update(context->CountVolumePercent(context->get_Map(), 1));
        print_Map(context->CountVolumePercent(context->get_Map(), 1));
        // нужно заимитить подсчет процентов

    }
}

void MainWindow::on_comboBoxSlot(const QString &str)
{
    if(str == "Folder strategy")
        return;
        //context->set_Strategy(std::make_shared<Folder_CalculationStrategy>());
    if(str == "File strategy")
        //context->set_Strategy(std::make_shared<Type_CalculationStrategy>());
        return;
}


MainWindow::~MainWindow(){}
