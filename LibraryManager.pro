#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T13:32:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryManager
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
        adminmainwindow.cpp \
    bookquerywidget.cpp \
    useradminwidget.cpp \
    insertbookwidget.cpp \
    booklist.cpp \
    deletebookwidget.cpp \
    visitormainwindow.cpp \
    usermainwindow.cpp \
    logindialog.cpp \
    regdialog.cpp \
    userloanwidget.cpp

HEADERS  += adminmainwindow.h \
    bookquerywidget.h \
    useradminwidget.h \
    insertbookwidget.h \
    booklist.h \
    deletebookwidget.h \
    visitormainwindow.h \
    usermainwindow.h \
    logindialog.h \
    regdialog.h \
    userloanwidget.h

FORMS    += adminmainwindow.ui \
    bookquerywidget.ui \
    useradminwidget.ui \
    insertbookwidget.ui \
    booklist.ui \
    deletebookwidget.ui \
    visitormainwindow.ui \
    usermainwindow.ui \
    logindialog.ui \
    regdialog.ui \
    userloanwidget.ui

DISTFILES += \
    ../db.sql

