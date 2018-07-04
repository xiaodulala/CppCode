#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    fTimer = new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000);
    connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_nowTimepushButton_clicked()
{
    //获取当前时间，为三个专用的编辑器设置日期时间数据，并且转换为字符串
    QDateTime curDateTime = QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->timeLineEdit->setText(curDateTime.toString("hh:mm:ss"));
    ui->dateEdit->setDate(curDateTime.date());
    ui->dateLineEdit->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(curDateTime);
    ui->dateTimeLineEdit->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void Dialog::on_pushButton_clicked()
{
    QString str = ui->timeLineEdit->text();
    str = str.trimmed();
    if(!str.isEmpty())
    {
        QTime time = QTime::fromString(str,"hh:mm:ss");
        ui->timeEdit->setTime(time);
    }
}

void Dialog::on_pushButton_2_clicked()
{
    QString str = ui->dateLineEdit->text();
    str = str.trimmed();
    if(!str.isEmpty()){
        QDate date=QDate::fromString(str,"yyyy-MM-dd");
        ui->dateEdit->setDate(date);
    }
}

void Dialog::on_pushButton_3_clicked()
{
    QString str = ui->dateTimeLineEdit->text();
    str.trimmed();
    if(!str.isEmpty())
    {
        QDateTime datetime = QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
    }
}

void Dialog::on_timer_timeout()
{
    //定时器中断响应
    QTime curtime = QTime::currentTime();
    ui->lcdHour->display(curtime.hour());
    ui->lcdMin->display(curtime.minute());
    ui->lcdSec->display(curtime.second());
    int va = ui->progressBar->value();
    if(va>100)
        va=0;
    ui->progressBar->setValue(va);
}

void Dialog::on_startButton_clicked()
{
    //定时器开始工作
    fTimer->start();
    //计时器开始工作
    fTimeCounter.start();
    ui->startButton->setEnabled(false);
    ui->endButton->setEnabled(true);
    ui->setLimit->setEnabled(false);
}

void Dialog::on_endButton_clicked()
{
    //定时器停止
    fTimer->stop();
    int tmMsec = fTimeCounter.elapsed();
    int ms = tmMsec%1000;
    int sec=tmMsec/1000;
    QString str = QString::asprintf("elapsTimes:%dSec,%dms",sec,ms).toLocal8Bit().data();
    ui->elapsTime->setText(str);
    ui->startButton->setEnabled(true);
    ui->endButton->setEnabled(false);
    ui->setLimit->setEnabled(true);
}
