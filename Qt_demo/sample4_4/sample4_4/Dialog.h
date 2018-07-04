#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include <QTime>
#include <QTimer>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_nowTimepushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //定时器溢出处理函数
    void on_timer_timeout();

    void on_startButton_clicked();

    void on_endButton_clicked();

private:
    Ui::Dialog *ui;
    //计时器
    QTime fTimeCounter;
    //定时器
    QTimer *fTimer;

};

#endif // DIALOG_H
