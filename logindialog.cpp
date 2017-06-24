#include "logindialog.h"
#include "ui_logindialog.h"

#include "visitormainwindow.h"
#include "ui_visitormainwindow.h"

#include "usermainwindow.h"
#include "ui_usermainwindow.h"

#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

#include "regdialog.h"
#include "ui_regdialog.h"

#include <QMessageBox>

LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void LogInDialog::on_pushButton_2_clicked(bool checked)
{
    VisitorMainWindow *v = new VisitorMainWindow;
    v->show();
    close();
}

void LogInDialog::on_regRushButton_clicked()
{
    RegDialog *r = new RegDialog(0, this);
    r->show();
    hide();
}

void LogInDialog::on_logInPushButton_clicked()
{
    if(ui->passwordLineEdit->text() == "" || ui->userLineEdit->text() == "")
    {
        QMessageBox::warning(0, tr("输入为空"), tr("用户名/密码为空！"));
    }
    else if(ui->logInComboBox->currentIndex() == 1)
    {
        adminQuery.exec("select password from admin where username = '"
                       + ui->userLineEdit->text() + "'");
        if(!adminQuery.isActive())
            return;

        if(adminQuery.next())
        {
            QString password = adminQuery.value(0).toString();
            if(QString::compare(password, ui->passwordLineEdit->text()) != 0)
            {
                QMessageBox::warning(0, tr("密码错误"), tr("请输入正确密码！"));
                return;
            }
        }
        else
        {
            QMessageBox::warning(0, tr("无此管理员"), tr("请输入正确管理员用户名！"));
            return;
        }

        AdminMainWindow *aw = new AdminMainWindow(0, ui->userLineEdit->text());//要传入个人信息
        aw->show();
        close();
    }
    else
    {
        userQuery.exec("select password from user where username = '"
                       + ui->userLineEdit->text() + "'");
        if(!userQuery.isActive())
            return;

        if(userQuery.next())
        {
            QString password = userQuery.value(0).toString();
            if(QString::compare(password, ui->passwordLineEdit->text()) != 0)
            {
                QMessageBox::warning(0, tr("密码错误"), tr("请输入正确密码！"));
                return;
            }
        }
        else
        {
            QMessageBox::warning(0, tr("无此用户"), tr("请输入正确用户名！"));
            return;
        }

        UserMainWindow *u = new UserMainWindow(0, ui->userLineEdit->text());//要传入个人信息
        u->show();
        close();
    }
}
