#include "usermainwindow.h"
#include "ui_usermainwindow.h"

UserMainWindow::UserMainWindow(QWidget *parent, QString name) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    userName = name;
    ui->userLabel->setText("当前用户:" + userName);
    ui->bookQueryTab->BookQueryWidget::username = name;
    ui->loanTab->userLoanWidget::username = name;
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::on_exitAction_triggered()
{
    QCoreApplication::exit();
}
