#ifndef VISITORMAINWINDOW_H
#define VISITORMAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "bookquerywidget.h"
#include "ui_bookquerywidget.h"

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;

namespace Ui {
class VisitorMainWindow;
}

class VisitorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VisitorMainWindow(QWidget *parent = 0);
    ~VisitorMainWindow();

private slots:
    void on_exitAction_triggered();

private:
    Ui::VisitorMainWindow *ui;
};

#endif // VISITORMAINWINDOW_H
