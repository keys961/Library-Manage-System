#ifndef USERADMINWIDGET_H
#define USERADMINWIDGET_H

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
class UserAdminWidget;
}

class UserAdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserAdminWidget(QWidget *parent = 0);
    ~UserAdminWidget();

private slots:
    void on_searchPushButton_clicked();

    void on_deleteUserPushButton_clicked();

    void on_authPushButton_clicked();

private:
    Ui::UserAdminWidget *ui;
};

#endif // USERADMINWIDGET_H
