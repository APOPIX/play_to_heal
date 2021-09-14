#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QString>
#include <stdio.h>
#include <QMessageBox>
#include <QDesktopWidget>
#include "settings.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_login_PushButton_clicked()//用户点击立即登录按钮
{
    //printf("用户点击登录按钮\n");
    if(!QString::compare(ui->input_user_name_LineEdit->text(),user)){
    //用户输入正确的用户名
    //跳转到功能选择页面;
        QMessageBox::information(NULL,"登录成功","您已成功登录系统");
        MainWindow* mainWindow = new MainWindow();
        mainWindow->showMaximized();//最大化显示
        //mainWindow->show();
        //窗口居中显示
        mainWindow->move((QApplication::desktop()->width() - mainWindow->width())/2,(QApplication::desktop()->height() - mainWindow->height())/2);
        //关闭窗口
        this->close();//destroy(true,false);
    }
}
