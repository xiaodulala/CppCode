#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"

QWMainWindow::QWMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWindow)
{
    ui->setupUi(this);
    iniUI();
    iniSignalSloats();
}

QWMainWindow::~QWMainWindow()
{
    delete ui;
}

void QWMainWindow::iniUI()
{
    //在状态栏上添加组件
    fLabCurFile = new QLabel;
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText("当前文件:");
    ui->statusBar->addWidget(fLabCurFile); //添加到状态栏

    progressBar1 = new QProgressBar;
    progressBar1->setMaximumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar1); //添加到状态栏

    //工具栏上添加组件  字体大小
    spinFontSize = new QSpinBox;
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue((ui->textEdit->font().pointSize()));
    spinFontSize->setMinimumWidth(50);
    ui->mainToolBar->addWidget(new QLabel("字体大小 "));
    ui->mainToolBar->addWidget(spinFontSize);

    ui->mainToolBar->addSeparator();//分隔条

    //工具栏 字体设置
    ui->mainToolBar->addWidget(new QLabel(" 字体"));
    comboFont = new QFontComboBox;
    comboFont->setMinimumWidth(150);
    ui->mainToolBar->addWidget(comboFont);
    setCentralWidget(ui->textEdit);
}

void QWMainWindow::iniSignalSloats()
{
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_comboFont_currentIndexChanged(QString)));
}

void QWMainWindow::on_actFontBold_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    if(checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}





void QWMainWindow::on_actFontItalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}



void QWMainWindow::on_actFontUnder_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}




void QWMainWindow::on_textEdit_selectionChanged()
{
    //选择文字在发生变化时信号被发射 用来改变字体设置的checked属性
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    ui->actFontBold->setChecked(fmt.font().bold()); //是否粗体
    ui->actFontItalic->setChecked(fmt.font().italic()); //是否斜体
    ui->actFontUnder->setChecked(fmt.fontUnderline()); //是否有下划线 有的话就让属性为选中状态
}

void QWMainWindow::on_textEdit_copyAvailable(bool b)
{
    //信号在有内容被选中时发射，用来改变复制和剪切的状态
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}


void QWMainWindow::on_spinBoxFontSize_valueChanged(int aFontSize)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(aFontSize);

}

void QWMainWindow::on_comboFont_currentIndexChanged(const QString &arg1)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);
    ui->textEdit->setCurrentCharFormat(fmt);
}



