#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QPerson.h"
namespace Ui {
class Widget;
}

class QMWidget : public QWidget
{
    Q_OBJECT
private:
    QPerson* boy;
    QPerson* girl;
public:
    explicit QMWidget(QMWidget *parent = 0);
    ~QMWidget();

private slots:
    //自定义槽函数
    void on_ageChanged(int value);
    void on_spin_valueChanged(int arg1);
    //界面槽函数
    void on_btnBoyInc_clicked();

    void on_btnGirlInc_clicked();

    void on_btnClassInfo_clicked();

    void on_btnClear_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
