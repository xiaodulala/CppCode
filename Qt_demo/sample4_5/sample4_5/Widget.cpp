#include "Widget.h"
#include "ui_Widget.h"
#include <QMenu>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QIcon icon;
    icon.addFile(":/images/images/Lighthouse.jpg");
    ui->comboBox->clear();

    for (int i=0;i<20;i++)
    {
        ui->comboBox->addItem(icon,QString::asprintf("Item %d",i));
        ui->comboBox->addItem(QString::asprintf("Item %d",i));
    }

    //如果只是添加字符串列表项 而且数据来源是一个QStringList变量 也可以使用addItems选项
    QStringList strList;
    strList << "北京" << "上海" << "天津" << "河北";
    ui->comboBox->addItems(strList);
}

void Widget::on_pushButton_3_clicked()
{
    QMap<QString,int> City_Zone;
    City_Zone.insert("北京",10);
    City_Zone.insert("上海",20);
    City_Zone.insert("天津",30);
    ui->comboBox_2->clear();
    foreach (const QString &str, City_Zone.keys()) {  //遍历所有的编号
        ui->comboBox_2->addItem(str,City_Zone.value(str));
    }
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    //有问题
    QString zone = ui->comboBox_2->currentData().toString(); //项关联的数据
    ui->plainTextEdit->appendPlainText(arg1+":区号="+zone);
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu* menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}
