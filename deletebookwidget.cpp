#include "deletebookwidget.h"
#include "ui_deletebookwidget.h"

#include <QTableWidgetItem>
#include <QTableWidget>
#include <QList>
#include <QMessageBox>
//extern QSqlDatabase db;
//extern QSqlQuery bookQuery;
//extern QSqlQuery loanQuery;
//extern QSqlQuery userQuery;

DeleteBookWidget::DeleteBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteBookWidget)
{
    ui->setupUi(this);
}

DeleteBookWidget::~DeleteBookWidget()
{
    delete ui;
}

void DeleteBookWidget::on_deletePushButton_clicked()
{
    bool isLent = false;
    QString deleteNum = ui->deleteNumSpinBox->text();
    int restNum;
    QList<QTableWidgetItem*> list = ui->deleteTableWidget->selectedItems();
    if(list.isEmpty())
    {
        QMessageBox::warning(0, "未选择任何项目", "请选择您要删除的书！");
        return;
    }

    QString bookId = list.at(0)->text();
    restNum = list.at(2)->text().toInt();
    loanQuery.exec("select * from loan where book_id = '" + bookId + "'");
    if(loanQuery.size() > 0)
        isLent = true;//True: If delete all, just update num to 0

    bookQuery.exec("update book set number = number - " + deleteNum + " "
                        "where book_id = '" + bookId + "'");
    if(restNum == deleteNum.toInt() && isLent == false)
        bookQuery.exec("delete from book where book_id = '" + bookId + "'");

    on_refreshPushButton_clicked();
}

void DeleteBookWidget::on_refreshPushButton_clicked()
{
    ui->deleteTableWidget->setRowCount(0);
    bookQuery.exec("select * from book where number > 0");
    ui->deleteTableWidget->setRowCount(bookQuery.size());

    int row = 0;
    while(bookQuery.next())
    {
        for(int i = 0; i < 8; i++)
        {
            ui->deleteTableWidget->setItem(row, i,
                                           new QTableWidgetItem(bookQuery.value(i).toString()));
        }
        row++;
    }
    ui->deleteTableWidget->show();
}

void DeleteBookWidget::on_deleteTableWidget_cellClicked(int row, int column)
{
    int restNum = ui->deleteTableWidget->item(row, 2)->text().toInt();
    ui->deleteNumSpinBox->setMaximum(restNum);
}
