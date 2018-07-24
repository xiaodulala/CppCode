#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LabFileName = new QLabel("");
    ui->statusBar->addWidget(LabFileName);
    this->setCentralWidget(ui->scrollArea);
    initTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTree()
{
    QString dataStr = "";//Item的Data存储的string
    ui->treeWidget->clear();
    QIcon icon;
    icon.addFile(":/imagesIcon/icons/Pictures_Picture_Folder_48px_515430_easyicon.net.png");

    //创建一个树节点
    QTreeWidgetItem* item = new QTreeWidgetItem(MainWindow::itTopItem);//自己定义的常量 节点类型
    item->setIcon(MainWindow::colItem,icon);//第一列的图标
    item->setText(MainWindow::colItem,"图片文件");//第一列的文字
    item->setText(MainWindow::colItemType,"type=itTopItem");
    //节点属性  Qt::Flags里面找
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    //setData 为节点的某一列设置一个角色数据
    item->setData(MainWindow::colItem,Qt::UserRole,QVariant(dataStr));
    //添加顶层节点
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::on_actAddFloder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory();//选择目录
    if(!dir.isEmpty()){
       QTreeWidgetItem *parItem = ui->treeWidget->currentItem();//当前节点
       if(parItem==NULL)
           return;
       addFolderItem(parItem,dir);
     }
}

//添加组节点操作
void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{
    //准备图标
    QIcon icon(":/imagesIcon/icons/folder_48px_42551_easyicon.net.png");
    //获得最后的文件夹名称
    QString NodeText= getFinalFolderName(dirName);

    //创建树节点
    QTreeWidgetItem* item;
    item = new QTreeWidgetItem(MainWindow::itGroupItem);//组节点
    item->setIcon(colItem,icon);
    item->setText(colItem,NodeText);
    item->setText(colItemType,"type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(dirName));
    parItem->addChild(item);
}

//获取最后的文件夹名称
QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt-i-1);
    return str;
}


//添加图片文件节点槽函数
void MainWindow::on_actAddFiles_triggered()
{
    int i = 0;
    i++;
    QStringList files = QFileDialog::getOpenFileNames(this,"选择一个或多个文件","","Images(*.png *.jpg *.icon *.jpeg)");
    if(files.isEmpty())
        return;
    QTreeWidgetItem *parrentItem,*item;
    item = ui->treeWidget->currentItem();
    if(item->type()==itImageItem)  //当前节点是图片节点 (图片节点是最后一层)
        parrentItem = item->parent(); //找到父节点
    else
        parrentItem = item;

    for(int i=0;i<files.size();i++){
        QString aFilename = files.at(i);//得到一个文件名
        addImageItem(parrentItem,aFilename);//添加一个图片节点
    }

}
//添加图片文件节点操作
void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFilename)
{
    //添加一个图片节点
    QIcon icon(":/imagesIcon/icons/Picture_48px_507712_easyicon.net.png");
    QString NodeText = getFinalFolderName(aFilename);
    QTreeWidgetItem* item;
    item = new QTreeWidgetItem(MainWindow::itImageItem);//节点类型是图片节点
    item->setIcon(colItem,icon);
    item->setText(colItem,NodeText);
    item->setText(colItem,"type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(aFilename));
    parItem->addChild(item);
}



//节点发生变化后连接的槽函数
void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    //当前节点变化时的处理
    Q_UNUSED(previous);
    if(current==NULL)
        return;
    int var  = current->type();
    switch(var){
    case itTopItem: //顶层节点
        ui->actAddFloder->setEnabled(true);
        ui->actAddFiles->setEnabled(true);
        ui->actDeleteItem->setEnabled(false);//顶层节点不能删除
        break;
    case itGroupItem:
        ui->actAddFloder->setEnabled(true);
        ui->actAddFiles->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        break;
    case itImageItem:
        ui->actAddFloder->setEnabled(false);//图片节点下不能添加目录节点
        ui->actAddFiles->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        displayImage(current);//显示图片
        break;
    }
}

//删除节点 必须用父节点删除子节点
void MainWindow::on_actDeleteItem_triggered()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    QTreeWidgetItem* parItem = item->parent();
    parItem->removeChild(item);
    delete item;
}
//遍历节点
void MainWindow::on_actScanItems_triggered()
{
    for(int i=0;i<ui->treeWidget->topLevelItemCount();i++){
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        changeItemCaption(item);
    }
}

//修改节点标题文字
void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*"+item->text(colItem);
    item->setText(colItem,str);
    if(item->childCount()>0)
        for(int i = 0;i<item->childCount();i++)//遍历子节点
            changeItemCaption(item->child(i)); //递归调用 可重入函数
}

//显示图片
void MainWindow::displayImage(QTreeWidgetItem *item)
{
    //返回节点存储的数据 也就是之前用setdata存储的数据
    QString filename = item->data(colItem,Qt::UserRole).toString();
    LabFileName->setText(filename);
    curPixmap.load(filename);//之前在h文件中定义的类型 可以直接载入图片
    //ui->label->setPixmap(curPixmap); 调整 自动适应显示槽函数中再显示
    on_actZoomFith_triggered();
}



void MainWindow::on_actZoomIn_triggered()
{
    pixRatio  = pixRatio*1.2; //缩放比例
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    QPixmap pix = curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomOut_triggered()
{
    pixRatio = pixRatio/1.2;
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    QPixmap pix = curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomFith_triggered()
{
    int h=ui->scrollArea->height();
    int realH = curPixmap.height();
    pixRatio = float(h)/realH;//当前显示比例 必须转换为浮点数
    QPixmap pix = curPixmap.scaledToHeight(h-30);
    ui->label->setPixmap(pix);
}



void MainWindow::on_actZoomFitW_triggered()
{
    int w = ui->scrollArea->width();
    int realW = curPixmap.width();
    pixRatio= float(w)/realW;
    QPixmap pix = curPixmap.scaledToWidth(w-30);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio = 1;
    ui->label->setPixmap(curPixmap);
}

//停靠槽函数
void MainWindow::on_actDockVisible_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}

//浮动槽函数
void MainWindow::on_actDockFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}

//关闭docker按钮槽函数--跟新工具栏按钮状态
void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}

//拖动docker--跟新工具栏按钮状态
void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}
