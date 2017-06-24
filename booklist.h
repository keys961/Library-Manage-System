#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;

namespace Ui {
class BookList;
}

class BookList : public QWidget
{
    Q_OBJECT

public:
    explicit BookList(QWidget *parent = 0);
    Ui::BookList *ui;
    ~BookList();

private slots:
    void on_refreshPushButton_clicked();

private:
};

#endif // BOOKLIST_H
