#include "visitormainwindow.h"
#include "ui_visitormainwindow.h"

VisitorMainWindow::VisitorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisitorMainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->ui->loanPushButton->setEnabled(false);
}

VisitorMainWindow::~VisitorMainWindow()
{
    delete ui;
}

void VisitorMainWindow::on_exitAction_triggered()
{
    QCoreApplication::exit();
}
