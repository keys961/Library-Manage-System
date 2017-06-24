#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "logindialog.h"

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;
extern QSqlQuery userQuery;
extern QSqlQuery adminQuery;

namespace Ui {
class RegDialog;
}

class RegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegDialog(QWidget *parent = 0, LogInDialog* d = 0);
    ~RegDialog();

private slots:
    void on_regPushButton_clicked();

private:
    Ui::RegDialog *ui;
    LogInDialog* dialog;
};

#endif // REGDIALOG_H
