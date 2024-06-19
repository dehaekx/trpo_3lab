QT = core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # сделал так, чтобы подключились библиотеки QMainWindow и тд
CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        calculationstrategy.cpp \
        context.cpp \
        fileexplorermodel.cpp \
        folder_strategy.cpp \
        main.cpp \
        mainwindow.cpp \
        type_strategy.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    calculationstrategy.h \
    context.h \
    fileexplorermodel.h \
    folder_strategy.h \
    mainwindow.h \
    type_strategy.h
