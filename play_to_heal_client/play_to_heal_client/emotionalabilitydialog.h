#ifndef EMOTIONALABILITYDIALOG_H
#define EMOTIONALABILITYDIALOG_H

#include <QDialog>
#include <commandlinethread.h>

namespace Ui {
class EmotionalAbilityDialog;
}

class EmotionalAbilityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmotionalAbilityDialog(QWidget *parent = 0);
    ~EmotionalAbilityDialog();

private slots:
    void on_startEmotionEvaluationPushButton_clicked();

private:
    Ui::EmotionalAbilityDialog *ui;
    CommandLineThread* cmdThread;
};

#endif // EMOTIONALABILITYDIALOG_H
