#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;
extern QSqlQuery userQuery;
extern QSqlQuery adminQuery;

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(QWidget *parent = 0);
    ~LogInDialog();

private slots:
    void on_pushButton_2_clicked(bool checked);

    void on_regRushButton_clicked();

    void on_logInPushButton_clicked();

private:
    Ui::LogInDialog *ui;
};

#endif // LOGINDIALOG_H
