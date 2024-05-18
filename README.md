# trpo_3lab
Лабораторная №3 [ Файловый обозреватель ]
Реализуем приложение  - "Файловый Обозреватель"

Общая постановка задачи находится здесь 

Основное назначение приложения - отображение размера файлов в процентах, сгруппированных по двум стратегиям:

1. файлы сгруппированы по папкам:

2. файлы сгруппированы по типам.

Требования.

Лабораторную сдаем по частям.

Общие требования:

- для оформления основного кода используем информацию, представленную для знакомства на занятии №1 .

- программа не должна иметь утечек памяти и/или падений вследствие необработанных исключений. В качестве доказательства преподаватель вправе потребовать предоставить тестовое покрытие для программы (в виде текстового списка: входные данные/действия - реакция программы).

 - код программы должен быть снабжен подробными комментариями. Для каждого метода/функции описывается ее назначение, назначение входных и возвращаемых параметров. Если параметры функции/метода имеют сложную структуру, то структура также описывается (состав и назначение полей).   

Для каждой части, нужно подготовить отчет, в котором в свободной форме описывается постановка задачи, предлагаемое решение в виде архитектуры ПО и набор вспомогательных разработанных функций. 

При описании архитектуры указывается набор используемых паттернов, включая объяснение их применения в конкретном решении.

Организация работы с репозиторием: (обсуждалось на занятии)

- основная разработка ведётся в ветке dev, допускается создание дополнительных веток, если это необходимо.
- сообщения коммитов отражают совершённые в коммите изменения. Детальное описание размещается в комментарии к коммиту. Недопустимы односложные/неинформативные/содержащие множественные опечатки коммиты (примеры: "fix", "final", "вроде всё" и т.п.).
- в ветку master сливаются только готовые версии программы.

Часть №1.(сдать до  19.05.24)

В первой части отдельным консольным приложением реализуем основную функцию –  вычисление размера, в зависимости от стратегии (см. Примерный вариант применения паттерна стратегии  ).

Общий принцип работы следующий: пользователь указывает директорию, для которой требуется вычислить размер содержимого.
Функция, в зависимости от выбранной стратегии, проводит вычисление, где результатом является набор соответствующих данных, вида

список файлов и папок (только верхнего уровня) / список типов файлов, содержащихся в директории(см. примеры в лекции ), а также занимаемый ими объём в процентах (точность два знака после запятой; если точности не хватает, а размер элемента не равен нулю, требуется это показать - например, в виде "< 0.01%").

Основная цель – проработка всевозможных условий. С целью доказательства того факта, что всевозможные условия обработаны, требуется подготовить тесты (примеры), на которых будете демонстрировать состоятельность вашей функции.

Готовую часть №1 сливаем в main/master

Часть №2(сдать до ... 26.05.24 )

Во второй части требуется реализовать приложение с графическим интерфейсом.

Требуется изучить концепцию MVC и её реализацию в Qt, материал находится здесь.

Рассмотрев предложенный пример (For_Lab3_partA.rar), требуется разработать модель, данные в которой будут заполняться с помощью реализованных ранее стратегий обхода содержимого папки.

Модель должна содержать,  название и занимаемый объём в процентах. 
В примере используется модель файловой системы (QFileSystemModel), отображаемая в двух представлениях: QTreeView (слева) и QTableView (справа).

После реализации вашей модели, достаточно просто сменить тип отображаемой модели у QTableView.

Таким образом, пользователь, выбрав директорию в левой части окна, тем самым запускает процесс её сканирования и может увидеть содержимое директории (относительно заданного типа группировки) в правой части окна.

Соответственно, также требуется доработать графический интерфейс, позволив пользователю выбирать способ группировки содержимого.

Общие сведения по MVC:
https://doc.qt.io/qt-5/model-view-programming.html
https://doc.qt.io/qt-5/modelview.html
+ Лекции.

Примеры создания конкретной модели:

https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

Пример создания модели с лекций   
