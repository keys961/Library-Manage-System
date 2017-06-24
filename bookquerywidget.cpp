#include "bookquerywidget.h"
#include "ui_bookquerywidget.h"
#include <QStringList>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

BookQueryWidget::BookQueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookQueryWidget)
{
    ui->setupUi(this);

    QStringList list;
    for(int i = 0; i < 13; i++)
        list.append(catagory[i]);
    ui->catagoryComboBox->addItems(list);

//    ui->queryTableWidget->clear();
//    ui->queryTableWidget
}

BookQueryWidget::~BookQueryWidget()
{
    delete ui;
}

void BookQueryWidget::on_searchPushButton_clicked()
{
    int flag = 0;
    QString bookName = ui->nameLineEdit->text();
    QString publisher = ui->pressLineEdit->text();
    QString author = ui->writerLineEdit->text();
    QString catagory = ui->catagoryComboBox->currentText();
    //int status = ui->statusComboBox->currentIndex();
    QString lowerYear = ui->lowerYearSpinBox->text();
    QString upperYear = ui->upperYearSpinBox->text();
    int lower = ui->lowerYearSpinBox->value();
    int upper = ui->upperYearSpinBox->value();

    QString query = "select book_id from book ";

    if(lower > upper && lower > 0 && upper > 0)
    {
        QMessageBox::warning(0, tr("错误"), tr("年份输入有误！"));
        return;
    }

    if(QString::compare(bookName, ""))
    {
        query.append("where name like '%" + bookName + "%' ");
        flag = 1;
    }
    if(QString::compare(publisher, ""))
    {
        if(flag == 0)
        {
            query.append("where publisher = '" + publisher + "' ");
            flag = 1;
        }
        else
            query.append("AND publisher = '" + publisher + "' ");
    }
    if(QString::compare(author, ""))
    {
        if(flag == 0)
        {
            query.append("where author = '" + author + "' ");
            flag = 1;
        }
        else
            query.append("AND author = '" + author + "' ");
    }
    if(QString::compare(catagory, ""))
    {
        if(flag == 0)
        {
            query.append("where type = '" + catagory + "' ");
            flag = 1;
        }
        else
            query.append("AND type = '" + catagory + "' ");
    }

    if(lower > 0 && upper <= 0)
    {
        if(flag == 0)
        {
            query.append("where publish_year >= '" + lowerYear + "' ");
            flag = 1;
        }
        else
            query.append("AND publish_year >= '" + lowerYear + "' ");
    }
    else if(lower <= 0 && upper > 0)
    {
        if(flag == 0)
        {
            query.append("where publish_year <= '" + upperYear + "' ");
            flag = 1;
        }
        else
            query.append("AND publish_year <= '" + upperYear + "' ");
    }
    else if(lower > 0 && upper > 0)
    {
        if(flag == 0)
        {
            query.append("where publish_year <= '" + upperYear +
                         "' AND publish_year >= '" + lowerYear + "'");
            flag = 1;
        }
        else
            query.append("AND publish_year <= '" + upperYear +
                         "' AND publish_year >= '" + lowerYear + "'");
    }

    QString loan = "select book_id from loan";
    searchUpdateTableWidget(query, loan);
}

void BookQueryWidget::searchUpdateTableWidget(QString book, QString loan)
{
    //QTableWidgetItem item;
    QSqlQuery temp = QSqlQuery(db);
    int status = ui->statusComboBox->currentIndex();
    ui->queryTableWidget->clearContents();

    if(status == 0)
        bookQuery.exec(book);
    else if(status == 1)
    {
        bookQuery.exec("select book_id from book "
                       "where number > 0");

        //bookQuery.exec(book + " minus " + loan);
    }
    else
    {
        bookQuery.exec("select book_id, COUNT(*) from (" + book
                       + " UNION ALL " + loan + ")a GROUP BY book_id HAVING COUNT(*) > 1");
    }
    int row = 0;
    ui->queryTableWidget->setRowCount(bookQuery.size());
    while(bookQuery.next())
    {
        temp.exec("select * from book where book_id = '"
        + bookQuery.value(0).toString() + "'");
        temp.next();
        for(int i = 0; i < 8; i++)
        {
            //item.setData(temp.value(i).toString());
            ui->queryTableWidget->setItem(row, i,
                                          new QTableWidgetItem(temp.value(i).toString()));
        }
        row++;
    }
    ui->queryTableWidget->show();
}

void BookQueryWidget::on_clearPushButton_clicked()
{
    ui->queryTableWidget->clearContents();
    ui->queryTableWidget->setRowCount(0);
}

void BookQueryWidget::on_loanPushButton_clicked()
{
    int flag = 0;
    userQuery.exec("select authority from user where username = '"
                   + username + "'");
    if(userQuery.next())
    {
        flag = userQuery.value(0).toInt();
    }
    if(flag == 0)
    {
        QMessageBox::warning(0, "无借书权限", "您无借书权限！");
        return;
    }
    else //有权限
    {
        loanQuery.exec("select book_id from loan where username like '"
                       + username + "'");
        if(!loanQuery.isActive())
        {
            QMessageBox::warning(0, "内部错误", "出现内部错误！");
            return;
        }
        if(loanQuery.size() >= 2) //超过数量
        {
            QMessageBox::warning(0, "借书书目超量", "您最多只能借2本书！");
            return;
        }
        else //借书！
        {
            int number;
            QList<QTableWidgetItem*> list = ui->queryTableWidget->selectedItems();
            if(list.isEmpty())
            {
                QMessageBox::warning(0, "未选择任何项目", "请选择您要借阅的书！");
                return;
            }
            QString bookId = list.at(0)->text();
            QDate d = QDate::currentDate();
            QString date = d.toString("yyyy-MM-dd");
            int loanNumber = 0;

            bookQuery.exec("select number from book where book_id = '"
                           + bookId + "'");
            if(!bookQuery.isActive())
            {
                QMessageBox::warning(0, "内部错误", "出现内部错误！");
                return;
            }
            if(bookQuery.next())
            {
                number = bookQuery.value(0).toInt();
                if(number == 0)
                {
                    QMessageBox::warning(0, "库存不足", "库存不足！");
                    return;
                }
                else
                {
                    loanQuery.exec("select loan_number from loan where book_id = '"
                                   + bookId + "'");
                    loanNumber = loanQuery.size();

                    loanQuery.exec("insert into loan values ('"
                                   + username + "','"
                                   + bookId + "','"
                                   + date + "',"
                                   + QString::number(loanNumber)
                                   + ")");
                    if(loanQuery.isActive())
                    {
                        bookQuery.exec("update book set "
                                       "number = number - 1 where book_id = '"
                                        + bookId + "'");

                        on_searchPushButton_clicked();
                    }
                    else
                    {
                       // qDebug() << loanQuery.lastError();
                        QMessageBox::warning(0, "内部错误", "借书失败！");
                        return;
                    }
                }
            }
        }
    }
}
