#include "Widget.h"
#include "ui_Widget.h"
#include <QMetaObject>
#include <QMetaProperty>
QMWidget::QMWidget(QMWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //构造一个男孩对象
    boy = new QPerson("wangxiaoming");
    //设置对象属性
    boy->setProperty("score",95);
    boy->setProperty("age",10);
    //设置动态属性，类型中没有定义此属性  动态属性只指针对象
    boy->setProperty("sex","Boy");
    //使用了指针方式的信号与槽的关联 因为QPerson只有一个ageChanged信号 没有同名的重载信号函数
    connect(boy,&QPerson::ageChanged,this,&QMWidget::on_ageChanged);

    //构造一个女孩对象
    girl = new QPerson("zhangxiaoli");
    girl->setProperty("score",81);
    girl->setProperty("age",10);
    girl->setProperty("sex","Girl");
    connect(girl,&QPerson::ageChanged,this,&QMWidget::on_ageChanged);

    //给控件增加动态属性
    ui->spinBoxBoy->setProperty("isBoy",true);
    ui->spinBoxGirl->setProperty("isGirl",false);
    //界面按钮自定义槽函数连接
    connect(ui->spinBoxBoy,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));
    connect(ui->spinBoxGirl,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));
}

QMWidget::~QMWidget()
{
    delete ui;
}

//用于响应QPerson的ageChanged信号
void QMWidget::on_ageChanged(int value)
{
    Q_UNUSED(value);
    //获取信号发射者，因为信号发射者是QPerson类型的对象boy或者girl 可以用下面函数将发射者投射为具体的类型
    QPerson* aPerson = qobject_cast<QPerson*>(sender());
    //通过类型指针 获取对象的属性值
    QString hisName = aPerson->property("name").toString();
    //也可以获得动态属性
    QString hisSex = aPerson->property(("sex")).toString();
    //通过接口获取年龄
    int hisAge = aPerson->age();
    //也可以通过属性获取年龄
    //int hisAge = aPerson->property("age").toInt();
    ui->textEdit->append(hisName + ","+hisSex+QString::asprintf(",年龄=%d",hisAge));
}

void QMWidget::on_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox->property("isBoy").toBool())
        boy->setAge(spinBox->value());
    else
        girl->setAge(spinBox->value());
}

void QMWidget::on_btnBoyInc_clicked()
{
    boy->setAge(boy->age()+1);
}

void QMWidget::on_btnGirlInc_clicked()
{
    girl->setAge(girl->age()+1);
}

void QMWidget::on_btnClassInfo_clicked()
{
    //metaObject()获得对象boy的元对象信息 这个类封装了访问类的元对象各种接口函数
    const QMetaObject* meta = boy->metaObject();
    ui->textEdit->clear();
    ui->textEdit->append("==元对象信息==\n");
    ui->textEdit->append(QString("类名称:%1\n").arg(meta->className()));
    ui->textEdit->append("prperty");
    for(int i = meta->propertyOffset();i<meta->propertyCount();++i)
    {
        QMetaProperty prop = meta->property(i);
        const char* propName = prop.name();
        QString propValue = boy->property(propName).toString();
        ui->textEdit->append(QString("属性名称=%1,属性名称=%2").arg(propName).arg(propValue));
    }

    ui->textEdit->append("");
    ui->textEdit->append("classinfo");
    for(int i=meta->classInfoOffset();i<meta->classInfoCount();i++)
    {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->textEdit->append(QString("Name=%1,Value=%2").arg(classInfo.name()).arg(classInfo.value()));
    }
}

void QMWidget::on_btnClear_clicked()
{
    ui->textEdit->clear();
}
