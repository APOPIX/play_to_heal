#include "scenecognitiondialog.h"
#include "ui_scenecognitiondialog.h"
#include "settings.h"
#include <opencv2/opencv.hpp>
#include <QMessageBox>
#include <QDebug>

SceneCognitionDialog::SceneCognitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneCognitionDialog)
{
    ui->setupUi(this);
    //初始化
    currentQuestion = 0;
    userAnswerList.clear();
    char imgSrc[500];
    std::sprintf(imgSrc,"%s%d.jpg",cognitiveImageDir.toUtf8().data(), currentQuestion);
    cv::Mat frame = cv::imread(imgSrc);
    QImage image;
    cvtColor(frame,frame,CV_BGR2RGB);
    image=QImage((const unsigned char*)(frame.data),
                frame.cols,frame.rows,QImage::Format_RGB888);
    ui->cognitiveTestImageLabel->setScaledContents(true);
    ui->cognitiveTestImageLabel->resize(ui->cognitiveTestImageLabel->width(),ui->cognitiveTestImageLabel->height());
    ui->cognitiveTestImageLabel->setPixmap(QPixmap::fromImage(image));
    ui->pushButtonA->setText(buttonA[currentQuestion]);
    ui->pushButtonB->setText(buttonB[currentQuestion]);
    ui->pushButtonC->setText(buttonC[currentQuestion]);
    ui->pushButtonD->setText(buttonD[currentQuestion]);
    currentQuestion++;
}

SceneCognitionDialog::~SceneCognitionDialog()
{
    delete ui;
}

void SceneCognitionDialog::fetchNextQuestion(int answer){
    userAnswerList.push_back(answer);
    //防止数组越界
    if(currentQuestion > numQuestions - 1){
        return;
    }
    char imgSrc[500];
    std::sprintf(imgSrc,"%s%d.jpg",cognitiveImageDir.toUtf8().data(), currentQuestion);
    cv::Mat frame = cv::imread(imgSrc);
    QImage image;
    cvtColor(frame,frame,CV_BGR2RGB);
    image=QImage((const unsigned char*)(frame.data),
                frame.cols,frame.rows,QImage::Format_RGB888);
    ui->cognitiveTestImageLabel->setScaledContents(true);
    ui->cognitiveTestImageLabel->resize(ui->cognitiveTestImageLabel->width(),ui->cognitiveTestImageLabel->height());
    ui->cognitiveTestImageLabel->setPixmap(QPixmap::fromImage(image));
    ui->pushButtonA->setText(buttonA[currentQuestion]);
    ui->pushButtonB->setText(buttonB[currentQuestion]);
    ui->pushButtonC->setText(buttonC[currentQuestion]);
    ui->pushButtonD->setText(buttonD[currentQuestion]);
    currentQuestion++;
}

int SceneCognitionDialog::countScore(){
    int score = 0;
    for(int i = 0; i<numQuestions; i++){
        //qDebug()<<userAnswerList[i]<< answerList[i]<<endl;
        if(userAnswerList[i] == answerList[i])
            score++;
    }
    return score;
}

void SceneCognitionDialog::allFinished(){
    //提示用户得分
    char information[100];
    int score = countScore();
    std::sprintf(information, "您本次测验的最终的分为%d分，再接再厉哦～", score);
    //关闭窗口
    this->close();//this->destroy(true, false);
    QMessageBox::information(this,"测验完成",information);

}

void SceneCognitionDialog::on_pushButtonA_clicked()
{
    fetchNextQuestion(0);
    if(currentQuestion == numQuestions){
        allFinished();
    }
}

void SceneCognitionDialog::on_pushButtonB_clicked()
{
    fetchNextQuestion(1);
    if(currentQuestion == numQuestions){
        allFinished();
    }
}

void SceneCognitionDialog::on_pushButtonC_clicked()
{
    fetchNextQuestion(2);
    if(currentQuestion == numQuestions){
        allFinished();
    }
}

void SceneCognitionDialog::on_pushButtonD_clicked()
{
    fetchNextQuestion(3);
    if(currentQuestion == numQuestions){
        allFinished();
    }
}
