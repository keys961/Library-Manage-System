#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "ui_bookquerywidget.h"

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;
extern QSqlQuery userQuery;
extern QSqlQuery adminQuery;

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = 0, QString name = "");
    ~AdminMainWindow();

private slots:
    void on_adminExitAction_triggered();

private:
    Ui::AdminMainWindow *ui;
    QString adminName;
};

#endif // ADMINMAINWINDOW_H
