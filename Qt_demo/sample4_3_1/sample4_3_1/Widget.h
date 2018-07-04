#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_redSlider_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_shiRadio_clicked();

    void on_erRadio_clicked();

    void on_baRadio_clicked();

    void on_shiliuRadio_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
