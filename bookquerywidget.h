#ifndef BOOKQUERYWIDGET_H
#define BOOKQUERYWIDGET_H

#include <QWidget>
#include <QDialog>
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
class BookQueryWidget;
}

class BookQueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookQueryWidget(QWidget *parent = 0);
    Ui::BookQueryWidget *ui;
    QString username;
    ~BookQueryWidget();

private slots:
    void on_searchPushButton_clicked();

    void on_clearPushButton_clicked();

    void on_loanPushButton_clicked();

private:

    QString catagory[13] =
        {"","哲学","社会科学","政治法律","军事","经济",
        "文体教育","文学","艺术","历史","自然科学",
        "工业技术","计算机"};

    void searchUpdateTableWidget(QString book, QString loan);
};

#endif // BOOKQUERYWIDGET_H
