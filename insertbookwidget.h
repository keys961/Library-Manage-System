#ifndef INSERTBOOKWIDGET_H
#define INSERTBOOKWIDGET_H

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
class InsertBookWidget;
}

class InsertBookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InsertBookWidget(QWidget *parent = 0);
    ~InsertBookWidget();
    QString username;
private slots:
    void on_insertPushButton_clicked();

private:
    Ui::InsertBookWidget *ui;
    QString catagory[13] =
        {"","哲学","社会科学","政治法律","军事","经济",
        "文体教育","文学","艺术","历史","自然科学",
        "工业技术","计算机"};
};

#endif // INSERTBOOKWIDGET_H
