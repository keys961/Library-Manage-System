#ifndef DELETEBOOKWIDGET_H
#define DELETEBOOKWIDGET_H

#include "booklist.h"
#include "ui_booklist.h"
#include <QWidget>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;
extern QSqlQuery userQuery;

namespace Ui {
class DeleteBookWidget;
}

class DeleteBookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteBookWidget(QWidget *parent = 0);
    ~DeleteBookWidget();
    //QString username;
private slots:
    void on_deletePushButton_clicked();

    void on_refreshPushButton_clicked();

    void on_deleteTableWidget_cellClicked(int row, int column);

private:
    Ui::DeleteBookWidget *ui;
};

#endif // DELETEBOOKWIDGET_H
