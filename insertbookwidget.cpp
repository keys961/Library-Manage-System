#include "insertbookwidget.h"
#include "ui_insertbookwidget.h"
#include <QMessageBox>
#include <QDate>

InsertBookWidget::InsertBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertBookWidget)
{
    ui->setupUi(this);
    for(int i = 0; i < 13; i++)
        ui->catagoryComboBox->addItem(catagory[i]);
}

InsertBookWidget::~InsertBookWidget()
{
    delete ui;
}

void InsertBookWidget::on_insertPushButton_clicked()
{
    QString bookName = ui->booknameLineEdit->text();
    QString number = ui->numberSpinBox->text();
    QString publisher = ui->publisherLineEdit->text();
    QString publishYear = ui->publishYearSpinBox->text();
    QString category = ui->catagoryComboBox->currentText();
    QString author = ui->authorLineEdit->text();

    bookQuery.exec("select book_id from book");
    int id = bookQuery.size();

    if(QString::compare(bookName, "") == 0 ||
            QString::compare(number, "0") == 0||
            QString::compare(publisher, "") == 0||
            QString::compare(category, "") == 0||
            QString::compare(author, "") == 0)
    {
        QMessageBox::warning(0, "输入信息不完整", "请输入完整且恰当的信息！");
        return;
    }

    bookQuery.exec("select * from book where name = '" + bookName + "' "
                   + "AND publisher = '" + publisher + "' "
                   + "AND publish_year = '" + publishYear + "' "
                   + "AND type = '" + category + "' "
                   + "AND author = '" + author + "'");
    if(!bookQuery.isActive())
    {
        QMessageBox::warning(0, "错误", "查询错误！");
        return;
    }

    if(bookQuery.next())
    {
        QString bookId = bookQuery.value(0).toString();
        bookQuery.exec("update book set number = number + " + number +
                       " where book_id = '" + bookId + "'");
        QMessageBox::information(0, "书目被合并", "书目: " + bookName + " 已被合并到已有条目！");
    }
    else
    {
        QDate d = QDate::currentDate();
        QString storeDate = d.toString("yyyy-MM-dd");
        bookQuery.exec("select book_id from book where book_id = '" +
                       QString::number(id) + "'");
        while(bookQuery.next())
        {
            id++;
            bookQuery.exec("select book_id from book where book_id = '" +
                           QString::number(id) + "'");
        }

        bookQuery.exec("insert into book values("
                        "'" + QString::number(id) + "',"
                        "'" + bookName + "',"
                       + number + ","
                        "'" + storeDate + "',"
                        "'" + publisher + "',"
                        "'" + publishYear + "',"
                        "'" + category + "',"
                        "'" + author + "')");
        if(bookQuery.isActive())
            QMessageBox::information(0, "成功", "书目: " + bookName + " 已被输入至数据库！");
    }
}
