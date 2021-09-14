#include "emotionalabilitydialog.h"
#include "ui_emotionalabilitydialog.h"
#include "commandlinethread.h"
#include "settings.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include <opencv2/opencv.hpp>


EmotionalAbilityDialog::EmotionalAbilityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmotionalAbilityDialog)
{
    ui->setupUi(this);
}

EmotionalAbilityDialog::~EmotionalAbilityDialog()
{
    delete ui;
}

void EmotionalAbilityDialog::on_startEmotionEvaluationPushButton_clicked()
{//开始情感评估,首先播放视频
    char command[500];
    QString fileName = "LeNozzediFigaro.mp4";
    std::sprintf(command,"omxplayer --win \"704 0 1280 384\" -o local %s/%s\n",emotionalAbilityDir.toUtf8().data(),fileName.toUtf8().data());
    qDebug()<<command<<endl;
    cmdThread =  new CommandLineThread(command);
    cmdThread->start();
    cv::VideoCapture capture(-1);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,576);//480的0.8倍
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,384);
    if(!capture.isOpened()){
        QMessageBox::information(NULL,"错误","摄像头打开失败，请检查摄像头链接！");
        return;
    }
    cv::Mat frame;
    std::string windowName = "实时摄像头";
    cv::namedWindow(windowName);
    //窗口靠右下
    int desktopWidth = QApplication::desktop()->width();
    int desktopHeight = QApplication::desktop()->height();
    cv::moveWindow(windowName, desktopWidth - 576, desktopHeight - 384);
    char imgName[200];
    int imgCount = 0;
    for(int i = 0; cmdThread->isRunning(); i++){
        capture >> frame;
        cv::imshow(windowName, frame);
        std::sprintf(imgName,"%s/%s_%d.jpg", faceDetectCache.toUtf8().data(),user.toUtf8().data(),imgCount);
        if(i%5==0){//每循环2次存储一张照片
            cv::imwrite(imgName,frame);
            imgCount++;
        }
        cv::waitKey(40);
    }
    //提示用户正在上传数据
    QMessageBox* upLoadWarning = new QMessageBox(QMessageBox::NoIcon,"提示","正在上传评估数据，请勿关闭窗口");
    upLoadWarning->show();
    //开始上传数据
    std::sprintf(command,"sshpass -p %s scp -v -r %s %s@%s:%s\n",
                 passWord.toUtf8().data(),
                 faceDetectCache.toUtf8().data(),
                 hostName.toUtf8().data(),
                 ipAddress.toUtf8().data(),
                 serverFaceDetectRecvCache.toUtf8().data());
    cmdThread = new CommandLineThread(command);
    cmdThread->start();
    cmdThread->wait();
    //向服务器传输finished.dat
    std::sprintf(command,"sshpass -p %s scp %s %s@%s:%s\n",
                 passWord.toUtf8().data(),
                 flagPath.toUtf8().data(),
                 hostName.toUtf8().data(),
                 ipAddress.toUtf8().data(),
                 serverFaceDetectFlagDir.toUtf8().data());
    qDebug()<<command<<endl;
    cmdThread = new CommandLineThread(command);
    cmdThread->start();
    cmdThread->wait();
    cmdThread->deleteLater();
    upLoadWarning->close();
    //收尾
    upLoadWarning->close();
    this->close();
    cmdThread->deleteLater();
    cv::destroyAllWindows();
}

