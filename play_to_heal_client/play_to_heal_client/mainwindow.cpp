#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gmfmdialog.h"
#include "scenecognitiondialog.h"
#include "emotionalabilitydialog.h"
#include <QDesktopWidget>
#include <opencv2/opencv.hpp>
#include <QDesktopWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_gmfmPushButton_clicked()
{
    GMFMDialog* gmfmDialog = new GMFMDialog(this);
    //左下角显示
    gmfmDialog->move(0,(QApplication::desktop()->height() - gmfmDialog->height()));
    gmfmDialog->show();
}

void MainWindow::on_cognitiveAbilityPushButton_clicked()
{
    SceneCognitionDialog* scenecognitiondialog = new SceneCognitionDialog();
    scenecognitiondialog->move((QApplication::desktop()->width() - scenecognitiondialog->width())/2,(QApplication::desktop()->height() - scenecognitiondialog->height())/2);
    scenecognitiondialog->show();
}

void MainWindow::on_emotionalComputingPushButton_clicked()
{//情感能力评估
    EmotionalAbilityDialog* emotionalAbilityDialog = new EmotionalAbilityDialog();
    emotionalAbilityDialog->move(QApplication::desktop()->width() - emotionalAbilityDialog->width(),QApplication::desktop()->height() - emotionalAbilityDialog->height());
    emotionalAbilityDialog->show();
}

void MainWindow::on_cameraAdjustingPushButton_clicked()
{//调节摄像头
    //取反
    cameraAdjusting = !cameraAdjusting;
    if(!cameraAdjusting)
        return;
    std::string windowName = "摄像头调节窗口";
    cv::Mat frame;
    cv::VideoCapture capture(-1);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,360);
    if(!capture.isOpened()){
        QMessageBox::information(NULL,"错误","摄像头打开失败，请检查摄像头链接！");
        return;
    }
    cv::namedWindow(windowName);
    //窗口居中
    cv::moveWindow(windowName, QApplication::desktop()->width() - 640, 0);
   while (cameraAdjusting){
       capture >> frame;
       cv::imshow(windowName, frame);
       cv::waitKey(40);
    }
   cv::destroyAllWindows();
   capture.release();
   cv::waitKey(100);
}
