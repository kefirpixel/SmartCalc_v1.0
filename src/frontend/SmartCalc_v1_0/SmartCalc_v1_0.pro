QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

ICON = logo3.png

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../backend/calculate.c \
    ../../backend/credit.c \
    ../../backend/deposit.c \
    ../../backend/formatting.c \
    ../../backend/stack.c \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../backend/calculate.h \
    ../../backend/formatting.h \
    ../../backend/stack.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
