#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include <QApplication>

AdminMainWindow::AdminMainWindow(QWidget *parent, QString name) :
    QMainWindow(parent),
    ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    adminName = name;
    ui->userLabel->setText("当前管理员:" + adminName);
    ui->bookQueryTab->BookQueryWidget::username = name;
    ui->insertBookTab->InsertBookWidget::username = name;
    ui->bookQueryTab->ui->loanPushButton->setEnabled(false);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::on_adminExitAction_triggered()
{
    QCoreApplication::exit();
}
