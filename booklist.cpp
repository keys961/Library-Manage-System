#include "booklist.h"
#include "ui_booklist.h"

BookList::BookList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookList)
{
    ui->setupUi(this);
}

BookList::~BookList()
{
    delete ui;
}

void BookList::on_refreshPushButton_clicked()
{
    bookQuery.exec("select * from book");
    ui->bookTableWidget->clearContents();
    ui->bookTableWidget->setRowCount(bookQuery.size());
    int row = 0;
    while(bookQuery.next())
    {
        for(int i = 0; i < 8; i++)
            ui->bookTableWidget->setItem(row, i,
                                         new QTableWidgetItem(bookQuery.value(i).toString()));
        row++;
    }
    ui->bookTableWidget->show();
}
