#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
namespace Ui {
class QWMainWindow;
}

class QWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWMainWindow(QWidget *parent = 0);
    void iniUI();
    void iniSignalSloats();
    ~QWMainWindow();

private slots:
    void on_actFontBold_triggered(bool checked);

    void on_actFontItalic_triggered(bool checked);

    void on_actFontUnder_triggered(bool checked);

    void on_textEdit_selectionChanged();

    void on_textEdit_copyAvailable(bool b);

    //改变字体大小的槽函数
    void on_spinBoxFontSize_valueChanged(int aFontSize);
    //改变字符的槽函数
    void on_comboFont_currentIndexChanged(const QString &arg1);


private:
    Ui::QWMainWindow *ui;
    QLabel *fLabCurFile; //状态栏里显示当前文件的label
    QProgressBar *progressBar1;//状态栏上的进度条
    QSpinBox *spinFontSize;//字体大小
    QFontComboBox *comboFont;

};

#endif // QWMAINWINDOW_H
