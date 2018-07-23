#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //使slitter分隔布局组件填满整个工作区
    setCentralWidget(ui->splitter);
    //设置QListWidget中的项的flags属性  ui中设计

    //手动绑定按钮和Action
    setActionForButton();
    createSelectionPopMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionForButton()
{
    ui->tBtnListIni->setDefaultAction(ui->actListIni);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);

}
 void MainWindow::createSelectionPopMenu()
 {
     //创建下拉菜单
     QMenu* menuSelection = new QMenu(this);
     //给菜单的每个项关联action
     menuSelection->addAction(ui->actSelAll);
     menuSelection->addAction(ui->actSelNone);
     menuSelection->addAction(ui->actSelInvs);
     //listWidget上方的按钮设置下拉菜单
     ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup); //设置成下拉菜单
     ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
     ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);//关联action
     ui->tBtnSelectItem->setMenu(menuSelection); //设置菜单  菜单想已经关联好action
     //工具栏上的 下拉式菜单按钮
     QToolButton* aBtn = new QToolButton(this);
     aBtn->setPopupMode(QToolButton::InstantPopup);
     aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//按钮样式
     aBtn->setMenu(menuSelection);
     ui->mainToolBar->addWidget(aBtn);

     ui->mainToolBar->addSeparator();
     ui->mainToolBar->addAction(ui->actQuit);
 }

//初始化列表
void MainWindow::on_actListIni_triggered()
{
    QListWidgetItem *aItem;//每一行是一个QListWidgetItem
    QIcon aIcon;
    aIcon.addFile(":/images/icos/point.png");
    bool chk = ui->checkBox->isCheckable();//是否可编辑
    ui->listWidget->clear();
    for(int i=0;i<10;i++){
        QString str = QString::asprintf("Item %d",i);
        aItem = new QListWidgetItem();
        aItem->setText(str); //设置项的文字
        aItem->setIcon(aIcon);//设置图标
        aItem->setCheckState(Qt::Checked);//设置为选中状态
        if(chk) //可编辑 设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else //不可编辑 设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);
    }
}



//插入项
void MainWindow::on_actListInsert_triggered()
{
    //准备一个icon对象给插入的项使用
    QIcon aIcon;
    aIcon.addFile(":/images/icos/point.png");
    bool chk = ui->checkBox->isChecked();
    QListWidgetItem *aItem = new QListWidgetItem("New Inserted Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if(chk) //可编辑 设置flags
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else //不可编辑 设置flags
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem);
}

//删除当前项
void MainWindow::on_actListDelete_triggered()
{
    //获取当前行号
    int row = ui->listWidget->currentRow();
    QListWidgetItem *aItem = ui->listWidget->takeItem(row);//takeItem只是移除项  需要使用delete删除
    delete aItem;//手工删除对象
}
//清空
void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}


//全选
void MainWindow::on_actSelAll_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i=0;i<cnt;i++){
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);
    }
}



void MainWindow::on_actSelNone_triggered()
{
    int cnt = ui->listWidget->count();
    for(int i=0;i<cnt;i++){
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}




void MainWindow::on_actSelInvs_triggered()
{
    int cnt = ui->listWidget->count();
    for(int i=0;i<cnt;i++){
        QListWidgetItem *aItem = ui->listWidget->item(i);
        bool chk = aItem->isSelected();
        if(chk)
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
    }
}
//当前选中项发生变化 槽函数
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if(current!=NULL){
        if(previous == NULL)
            str = "当前项:"+current->text();
        else
            str = "前一项:"+previous->text() +";当前项:"+current->text();
        ui->lineEdit->setText(str);
    }

}

//设置listWidget菜单项 右键点击槽函数
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos)
    QMenu* menuList = new QMenu(this);
    menuList->addAction(ui->actListIni);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);

    //在鼠标位置显示右键菜单
    menuList->exec(QCursor::pos());
    delete menuList;

}
