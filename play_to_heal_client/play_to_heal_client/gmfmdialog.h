#ifndef GMFMDIALOG_H
#define GMFMDIALOG_H

#include <QDialog>

namespace Ui {
class GMFMDialog;
}

class GMFMDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GMFMDialog(QWidget *parent = 0);
    ~GMFMDialog();

private slots:
    void on_start_GMFM_PushButton_clicked();

private:
    Ui::GMFMDialog *ui;
    bool running = false;//是否正在进行GMFM评估
};

#endif // GMFMDIALOG_H
