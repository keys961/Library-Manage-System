#include "regdialog.h"
#include "ui_regdialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>


RegDialog::RegDialog(QWidget *parent, LogInDialog* d) :
    QDialog(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);
    RegDialog::dialog = d;
}

RegDialog::~RegDialog()
{
    delete ui;
    //dialog->show();
}

void RegDialog::on_regPushButton_clicked()
{
    if(ui->usrLineEdit->text() == "" || ui->pwdLineEdit->text() == "")
    {
        QMessageBox::warning(NULL, tr("用户名/密码不能为空"), tr("用户名/密码不能为空"));
    }
    else if(ui->usrLineEdit->text().length() > 16 || ui->usrLineEdit->text().length() < 4
            || ui->pwdLineEdit->text().length() > 16 || ui->pwdLineEdit->text().length() < 4)
    {
        QMessageBox::warning(NULL, tr("用户名/长度非法"), tr("用户名/密码长度应该在4-16之间！"));
    }
    else if(ui->regComboBox->currentIndex() == 1)
    {
        adminQuery.exec("select username from admin where username = '"
                       + ui->usrLineEdit->text().trimmed() + "'");
        if(adminQuery.next())
            QMessageBox::warning(NULL, tr("用户名已被注册"), tr("用户名已被注册！"));
        else
        {
            adminQuery.exec("insert into admin values('" +
                           ui->usrLineEdit->text().trimmed() + "','"
                           + ui->pwdLineEdit->text() + "')");
            if(adminQuery.isActive())
            {
                QMessageBox::about(0, tr("注册成功"), tr("注册成功！"));
                close();
                dialog->show();
            }
            else
            {
                qDebug() << userQuery.lastError().text();
                QMessageBox::about(0, tr("注册失败"), tr("注册失败！"));
            }
        }
    }
    else
    {
            userQuery.exec("select username from user where username = '"
                           + ui->usrLineEdit->text().trimmed() + "'");
            if(userQuery.next())
                QMessageBox::warning(NULL, tr("用户名已被注册"), tr("用户名已被注册！"));
            else
            {
                userQuery.exec("insert into user values('" +
                               ui->usrLineEdit->text().trimmed() + "','"
                               + ui->pwdLineEdit->text() + "',"
                               + "'1')");
                if(userQuery.isActive())
                {
                    QMessageBox::about(0, tr("注册成功"), tr("注册成功！"));
                    close();
                    dialog->show();
                }
                else
                {
                   // qDebug() << userQuery.lastError().text();
                    QMessageBox::about(0, tr("注册失败"), tr("注册失败！"));
                }
            }
    }
}
