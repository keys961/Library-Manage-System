#include "adminmainwindow.h"
#include "visitormainwindow.h"
#include "logindialog.h"
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QTextCodec>

QSqlDatabase db;

QSqlQuery bookQuery;
QSqlQuery loanQuery;
QSqlQuery userQuery;
QSqlQuery adminQuery;

bool initialize();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);


    //AdminMainWindow w;
    //w.show();
    if(!initialize())
    {
        QMessageBox::critical(NULL, "初始化失败", "初始化失败！");
    }
    else
    {
        LogInDialog logInDialog;
        logInDialog.exec();
    }
    //return 0;
    return a.exec();
}

bool initialize()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("book_manager");
    db.setUserName("jintaoye");
    db.setPassword("123456");
    db.setPort(3306);

    if(!db.open())
    {
        qDebug() << QSqlDatabase::drivers();
        qDebug() << db.lastError().text();
        return false;
    }
    else
    {
        userQuery = QSqlQuery(db);
        loanQuery = QSqlQuery(db);
        bookQuery = QSqlQuery(db);
        adminQuery = QSqlQuery(db);
        return true;
    }
}
