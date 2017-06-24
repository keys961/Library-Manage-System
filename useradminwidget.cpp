#include "useradminwidget.h"
#include "ui_useradminwidget.h"
#include <QMessageBox>
#include <QString>

UserAdminWidget::UserAdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserAdminWidget)
{
    ui->setupUi(this);
}

UserAdminWidget::~UserAdminWidget()
{
    delete ui;
}

void UserAdminWidget::on_searchPushButton_clicked() //Search and Update
{
    ui->userTableWidget->setRowCount(0);
    QString userName = ui->userLineEdit->text();

    QString username, password, loanNumber, authority,
            bookId, bookName, loanDate;
    //QStringList loanInfo;

    if(QString::compare(userName, "") == 0)
        userQuery.exec("select * from user");
    else
        userQuery.exec("select * from user where username = '" + userName + "'");
    if(!userQuery.isActive())
    {
        QMessageBox::warning(0, "查询错误", "查询错误！");
        return;
    }

    ui->userTableWidget->setRowCount(userQuery.size());
    int row = 0;

    while(userQuery.next())
    {
        //book1 = date1 = book2 = date2 = "";
        //loanInfo.clear();
        username = userQuery.value(0).toString();
        password = userQuery.value(1).toString();
        authority = QString::compare(userQuery.value(2).toString(), "1") == 0?
                    "Yes" : "No";

        loanQuery.exec("select book_id, loan_date from loan where username = '" + username + "'");
        loanNumber = QString::number(loanQuery.size());

        int column = 4;
        while(loanQuery.next())
        {
            bookId = loanQuery.value(0).toString();
            bookQuery.exec("select name from book where book_id = '" + bookId + "'");
            if(bookQuery.next())
                bookName = bookQuery.value(0).toString();
            loanDate = loanQuery.value(1).toString();
            ui->userTableWidget->setItem(row, column++, new QTableWidgetItem(bookName));
            ui->userTableWidget->setItem(row, column++, new QTableWidgetItem(loanDate));
        }

        ui->userTableWidget->setItem(row, 0, new QTableWidgetItem(username));
        ui->userTableWidget->setItem(row, 1, new QTableWidgetItem(password));
        ui->userTableWidget->setItem(row, 2, new QTableWidgetItem(loanNumber));
        ui->userTableWidget->setItem(row, 3, new QTableWidgetItem(authority));
        row++;
    }

}

void UserAdminWidget::on_deleteUserPushButton_clicked() //Delete user
{
    QList<QTableWidgetItem*> list = ui->userTableWidget->selectedItems();
    QString userName = list.at(0)->text();
    int loanNum = list.at(2)->text().toInt();
    if(loanNum > 0)
    {
        QMessageBox::warning(0, "不能删除该用户", "该用户仍有书未归还，不能删除该用户！");
        return;
    }

    userQuery.exec("delete from user where username = '" + userName + "'");
    if(userQuery.isActive())
        QMessageBox::information(0, "删除成功", "用户： " + userName + " 删除成功！");
    on_searchPushButton_clicked();
}

void UserAdminWidget::on_authPushButton_clicked() //Change authority
{
    QList<QTableWidgetItem*> list = ui->userTableWidget->selectedItems();
    QString userName = list.at(0)->text();
    QString authority = list.at(3)->text();
    if(QString::compare(authority, "Yes") == 0)
        authority = "0";
    else
        authority = "1";

    userQuery.exec("update user set authority = " + authority +
                   " where username = '" + userName + "'");
    if(userQuery.isActive())
        QMessageBox::information(0, "更改成功", "用户： " + userName + " 权限更改成功！");
    on_searchPushButton_clicked();
}
