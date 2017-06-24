#include "userloanwidget.h"
#include "ui_userloanwidget.h"
#include <QMessageBox>

userLoanWidget::userLoanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userLoanWidget)
{
    ui->setupUi(this);
    //updateLoanTable();
}

userLoanWidget::~userLoanWidget()
{
    delete ui;
}

void userLoanWidget::on_returnPushButton_clicked()
{
   QList<QTableWidgetItem*> list =  ui->loanTableWidget->selectedItems();
   QString bookId = list.at(0)->text();
   QString bookName = list.at(1)->text();
   QString loanNumber = list.at(3)->text();

   loanQuery.exec("delete from loan where username = '" + username + "' "
                  "AND book_id = '" + bookId + "' "
                  "AND loan_number = " + loanNumber);
   bookQuery.exec("update book set number = number + 1"
                  " where book_id = '" + bookId + "'");
   updateLoanTable();
   if(bookQuery.isActive())
       QMessageBox::information(0, "归还成功", "书目: " + bookName + " 归还成功！");
}

void userLoanWidget::updateLoanTable()
{
    loanQuery.exec("select book_id, loan_date, loan_number from loan "
                   "where username = '" + username + "'");
    QString bookId;
    QString bookName;
    QString loanDate;
    QString loanNumber;

    if(!loanQuery.isActive())
    {
        QMessageBox::warning(0, "内部错误", "查询LOAN表错误！");
    }

    int row = 0;

    ui->loanTableWidget->setRowCount(loanQuery.size());

    while(loanQuery.next())
    {
        bookId = loanQuery.value(0).toString();
        loanDate = loanQuery.value(1).toString();
        loanNumber = loanQuery.value(2).toString();

        bookQuery.exec("select name from book where book_id = '"
                       + bookId + "'");
        if(bookQuery.next())
            bookName = bookQuery.value(0).toString();

        ui->loanTableWidget->setItem(row, 0, new QTableWidgetItem(bookId));
        ui->loanTableWidget->setItem(row, 1, new QTableWidgetItem(bookName));
        ui->loanTableWidget->setItem(row, 2, new QTableWidgetItem(loanDate));
        ui->loanTableWidget->setItem(row, 3, new QTableWidgetItem(loanNumber));
        row++;
    }
}

void userLoanWidget::on_refreshPushButton_clicked()
{
    updateLoanTable();
}
