QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS



SOURCES += \
    ../communicator/communicator.cpp \
    application.cpp \
    interface.cpp \
    main.cpp \
    mainwindow.cpp \
    matrixdisplaywindow.cpp


HEADERS += \
    application.h \
    interface.h \
    ../communicator/communicator.h \
    mainwindow.h \
    matrixdisplaywindow.h


FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
