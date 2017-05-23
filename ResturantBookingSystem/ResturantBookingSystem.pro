#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T16:40:39
#
#-------------------------------------------------

QT       += core gui
QT      +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ResturantBookingSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        walkin_dialog.cpp \
    addbooking_dialog.cpp \
    dbconnect.cpp \
    calendarstring.cpp \
    mycalendarbutton.cpp \
    calendarwidget.cpp \
    orderschart.cpp \
    modifyorder_dialog.cpp \
    mainwidget.cpp

HEADERS  += walkin_dialog.h \
    addbooking_dialog.h \
    dbconnect.h \
    calendarstring.h \
    mycalendarbutton.h \
    calendarwidget.h \
    orderschart.h \
    modifyorder_dialog.h \
    mainwidget.h

RESOURCES += \
    srcs.qrc
