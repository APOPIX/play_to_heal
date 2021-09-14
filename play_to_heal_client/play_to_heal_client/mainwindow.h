#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_gmfmPushButton_clicked();

    void on_cognitiveAbilityPushButton_clicked();

    void on_emotionalComputingPushButton_clicked();

    void on_cameraAdjustingPushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool cameraAdjusting = false;//为true时，可以进行摄像头调节
};

#endif // MAINWINDOW_H
