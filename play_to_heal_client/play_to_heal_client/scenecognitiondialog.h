#ifndef SCENECOGNITIONDIALOG_H
#define SCENECOGNITIONDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>

namespace Ui {
class SceneCognitionDialog;
}

class SceneCognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SceneCognitionDialog(QWidget *parent = 0);
    ~SceneCognitionDialog();

private slots:
    void on_pushButtonA_clicked();

    void on_pushButtonB_clicked();

    void on_pushButtonC_clicked();

    void on_pushButtonD_clicked();

    void fetchNextQuestion(int answer);

    int countScore();

    void allFinished();

private:
    Ui::SceneCognitionDialog *ui;
    int answerList[10] = {0,2,0,0,2,3,1,2,1,0};
    std::vector<int> userAnswerList;
    int currentQuestion = 0;
    int numQuestions = 10;
    char *buttonA[10]={"plane","apple","field","car","snow","sheep","boy","house","bike","minions"};
    char *buttonB[10]={"computer","pen","house","bike","city","ship","women","wolf","boy","chopsticks"};
    char *buttonC[10]={"person","building","pencil","pen","horse","TV","phone","mountain","chair","knife"};
    char *buttonD[10]={"wolf","car","horse","tree","fish","plane","car","water","cat","money"};
};

#endif // SCENECOGNITIONDIALOG_H
