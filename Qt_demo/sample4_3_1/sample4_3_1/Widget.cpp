#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    on_redSlider_valueChanged(20);
    QObject::connect(ui->greenSlider,SIGNAL(valueChanged(int)),this,SLOT(on_redSlider_valueChanged(int)));
     QObject::connect(ui->blueSlider,SIGNAL(valueChanged(int)),this,SLOT(on_redSlider_valueChanged(int)));
      QObject::connect(ui->alphaSlider,SIGNAL(valueChanged(int)),this,SLOT(on_redSlider_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_redSlider_valueChanged(int value)
{
    Q_UNUSED(value)
    QColor color;
    int R = ui->redSlider->value();
    int G = ui->greenSlider->value();
    int B = ui->blueSlider->value();
    int alpha = ui->alphaSlider->value();
    color.setRgb(R,G,B,alpha);
    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base,color);//设置底色
    ui->textEdit->setPalette(pal);
}

void Widget::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

void Widget::on_shiRadio_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();
}

void Widget::on_erRadio_clicked()
{
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setBinMode();
}


void Widget::on_baRadio_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setOctMode();
}

void Widget::on_shiliuRadio_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setHexMode();
}
