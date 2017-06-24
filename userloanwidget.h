#ifndef USERLOANWIDGET_H
#define USERLOANWIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;
extern QSqlQuery userQuery;

namespace Ui {
class userLoanWidget;
}

class userLoanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit userLoanWidget(QWidget *parent = 0);
    ~userLoanWidget();
    Ui::userLoanWidget *ui;
    QString username;

private slots:
    void on_returnPushButton_clicked();

    void on_refreshPushButton_clicked();

private:
    //Ui::userLoanWidget *ui;
    void updateLoanTable();
};

#endif // USERLOANWIDGET_H
