#include "gmfmdialog.h"
#include "ui_gmfmdialog.h"
#include <QProcess>
#include <opencv2/opencv.hpp>
#include <QMessageBox>
#include <QDesktopWidget>
#include <string>
#include <stdlib.h>
#include <QDebug>
#include <iostream>
#include <fstream>
#include "settings.h"
#include "commandlinethread.h"

GMFMDialog::GMFMDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GMFMDialog)
{
    ui->setupUi(this);
}

GMFMDialog::~GMFMDialog()
{
    delete ui;
}

void GMFMDialog::on_start_GMFM_PushButton_clicked()//用户进行GMFM测试
{
    this->running = true;
    char command[500];//存储命令行
    std::string windowName = "实时摄像头";
    //QString poseType = "GMFM57";//动作类型（已在settings.h中定义）
    int imgCount = 0;
    int desktopWidth = QApplication::desktop()->width();
    int desktopHeight = QApplication::desktop()->height();
    cv::VideoCapture capture(-1);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,576);//480的0.8倍
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,384);
    if(!capture.isOpened()){
        QMessageBox::information(NULL,"错误","摄像头打开失败，请检查摄像头链接！");
        return;
    }
    cv::Mat frame;
    cv::namedWindow(windowName);
    //窗口靠右下
    cv::moveWindow(windowName, desktopWidth - 576, desktopHeight - 384);
    char fileName[200];
    //使用omxplayer来播放标准动作的mp4视频
    //窗口靠右上
    std::sprintf(command,"omxplayer --win \"704 0 1280 384\" -o local GMFM_standard/%s.mp4\n", poseType.toUtf8().data());
    qDebug()<<command<<endl;
    CommandLineThread* cmdThread=  new CommandLineThread(command);
    cmdThread->start();
    for(int i = 0; cmdThread->isRunning(); i++){
        capture >> frame;
        cv::imshow(windowName, frame);
        std::sprintf(fileName,"%s/%s_%s_%d.jpg", gmfmCache.toUtf8().data(),user.toUtf8().data(),poseType.toUtf8().data(),imgCount);
        if(i%2==0){//每循环2次存储一张照片
            cv::imwrite(fileName,frame);
            imgCount++;
        }
        cv::waitKey(40);
    }
    cmdThread->deleteLater();
    //向服务器传输图片
    //QMessageBox* upLoadWarning = new QMessageBox(QMessageBox::NoIcon,"提示","正在上传评估数据，请勿关闭窗口");
    //upLoadWarning->show();
    std::sprintf(command,"sshpass -p %s scp -v -r %s %s@%s:%s\n",
                 passWord.toUtf8().data(),
                 gmfmCache.toUtf8().data(),
                 hostName.toUtf8().data(),
                 ipAddress.toUtf8().data(),
                 serverGmfmRecvCache.toUtf8().data());
    cmdThread = new CommandLineThread(command);
    cmdThread->start();
    cmdThread->wait();
    cmdThread->deleteLater();
    //向服务器传输finished.dat
    std::sprintf(command,"sshpass -p %s scp %s %s@%s:%s\n",
                 passWord.toUtf8().data(),
                 flagPath.toUtf8().data(),
                 hostName.toUtf8().data(),
                 ipAddress.toUtf8().data(),
                 serverGmfmEvalFlagDir.toUtf8().data());
    qDebug()<<command<<endl;
    cmdThread = new CommandLineThread(command);
    cmdThread->start();
    cmdThread->wait();
    cmdThread->deleteLater();
    //upLoadWarning->close();
    //收尾工作
    cv::destroyAllWindows();

    if( capture.isOpened() ){
        capture.release();
        cv::waitKey(100);
        qDebug()<<"关闭摄像头"<<endl;
    }
    this->close();
}
