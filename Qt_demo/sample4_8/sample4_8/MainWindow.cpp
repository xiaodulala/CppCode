#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter_2);
    //状态栏初始化创建
    labCellIndex = new QLabel("当前单元格坐标: ",this);
    labCellIndex->setMinimumWidth(250);
    labCellType = new QLabel("当前单元格类型: ",this);
    labCellType->setMinimumWidth(200);
    labStudID = new QLabel("学生ID: ",this);
    labStudID->setMinimumWidth(200);
    //加到状态栏
    ui->statusBar->addWidget(labCellIndex);
    ui->statusBar->addWidget(labCellType);
    ui->statusBar->addWidget(labStudID);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//设置表头
/*
   行表头各列的文字标题由一个QStringList对象headerText初始化存储。
   在一个表格中 不管是表头还是工作区 每个单元格都是一个QTableWidgetItem对象。对象中包含了单元格的所有内容
   字标题 格式设置 以及关联的数据。
*/
void MainWindow::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "姓 名" << "性 别" << " 出生日期" << "民 族" << "是否是党员" << "分 数";
    //如果单纯的设置表头 下面一句就够
    //ui->tableWidget->setHorizontalHeaderLabels(headerText);
    ui->tableWidget->setColumnCount(headerText.size());//设置列数
    //循环列数 给行的每列创建item对象
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font(); //对象中包含字体对象 设置这个对象
        font.setBold(true);//粗体
        font.setPointSize(12);//字体大小
        headerItem->setTextColor(Qt::red);
        headerItem->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
}

//根据表格的行数 生成数据填充表格 为每个单元格生成QTableWidgetItem对象
void MainWindow::on_btnIniData_clicked()
{
    //初始化表格内容
    QString strName,strSex;
    bool isParty=false;
    QDate birth;
    birth.setDate(1980,4,7);
    //只清楚工作区 不清楚表头
    ui->tableWidget->clearContents();
    int rows = ui->tableWidget->rowCount();//数据区行数
    for(int i=0;i<rows;i++)
    {
        strName = QString::asprintf("学生%d",i);
        if((i%2)==0)
            strSex="男";
        else
            strSex="女";
        createItemsARow(i,strName,strSex,birth,"汉族",isParty,70);
        birth = birth.addDays(20);//日期加20天
        isParty = !isParty;
    }
}

void MainWindow::createItemsARow(int rowNo, QString Name, QString Sex, QDate birth, QString Nation, bool isPM, int score)
{
    //为一行的单元格创建items
    QTableWidgetItem *item;
    QString str;
    uint StudyID = 201605000;//学号基数
    //姓名
    item = new QTableWidgetItem(Name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    StudyID +=rowNo;//学号等于基数加行号
    item->setData(Qt::UserRole,QVariant(StudyID));//设置单元格隐藏数据为学号
    ui->tableWidget->setItem(rowNo,MainWindow::colName,item);
    //性别
    QIcon icon;
    if(Sex=="男")
        icon.addFile(":/imagse/icons/icons/man.png");
    else{
        icon.addFile(":/imagse/icons/icons/woman.png");
    }
    item = new QTableWidgetItem(Sex,MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colSex,item);
    //出生日期
    str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str,MainWindow::ctBrith);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colBirth,item);
    //民族
    item = new QTableWidgetItem(Nation,MainWindow::ctBrith);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colNation,item);
    //是否是党员
    item = new QTableWidgetItem("党员",MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    if(isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackgroundColor(Qt::yellow);
    ui->tableWidget->setItem(rowNo,colPartyM,item);
    //分数
    str.setNum(score);
    item = new QTableWidgetItem(str,MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colScore,item);
}


//获取当前单元格数据显示在状态栏
void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousColumn);
    Q_UNUSED(previousRow);
    QTableWidgetItem* item = ui->tableWidget->item(currentRow,currentColumn);
    if(item == NULL)
        return;
    labCellIndex->setText(QString::asprintf("当前单元格的坐标: %d行，%d列",currentRow,currentColumn));
    //获取单元格类型
   int cellType = item->type();
   labCellType->setText(QString::asprintf("当前单元格的类型: %d",cellType));
   //学生的学号只有每行第一列的单元格中才保存 要获取本行第一列item
   item = ui->tableWidget->item(currentRow,MainWindow::colName);
   int ID = item->data(Qt::UserRole).toInt();
   labStudID->setText(QString::asprintf("学生ID: %d",ID));
}

 //插入一行
void MainWindow::on_btnInsertRow_clicked()
{
   int curRow = ui->tableWidget->currentRow();
   ui->tableWidget->insertRow(curRow); //插入一行 不会自动为单元格穿件item
   createItemsARow(curRow,"新学生","男",QDate::fromString("1990-1-1","yyyy-M-d"),"苗族",false,0);
}

void MainWindow::on_btnAppendRow_clicked()
{
    int curRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(curRow); //尾部添加
    createItemsARow(curRow,"新学生","女",QDate::fromString("1992-1-5","yyyy-M-d"),"满族",false,0);
}

void MainWindow::on_btnDelCurRow_clicked()
{
    int curRow = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(curRow);
}

//调整行高
void MainWindow::on_btnResizeHigh_clicked()
{

   ui->tableWidget->resizeRowsToContents();
}
//调整列宽
void MainWindow::on_btnResieWidth_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}


//设置编辑模式
void MainWindow::on_checkBoxEditable_clicked(bool checked)
{
    if(checked)
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
    else
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//隔行换色
void MainWindow::on_checkBoxRowColor_clicked(bool checked)
{
    ui->tableWidget->setAlternatingRowColors(checked);
}



void MainWindow::on_checkBoxHeaderH_clicked(bool checked)
{
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}

void MainWindow::on_checkBoxHeaderV_clicked(bool checked)
{
    ui->tableWidget->verticalHeader()->setVisible(checked);
}

void MainWindow::on_radioSelectRow_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_radioSelectItem_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void MainWindow::on_btnSetRowCount_clicked()
{
    int rowCount = ui->spinBox->text().toInt();
    ui->tableWidget->setRowCount(rowCount);
}

void MainWindow::on_pushButton_9_clicked()
{
    //将所有单元格的内容提取到字符串 显示
    QString str;
    QTableWidgetItem* cellItem;
    ui->plainTextEdit->clear();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        str = QString::asprintf("第 %d 行: ",i+1);
        for(int j=0;j<ui->tableWidget->columnCount()-1;j++)
        {
            cellItem = ui->tableWidget->item(i,j);
            str = str+cellItem->text()+" ";
        }
        cellItem = ui->tableWidget->item(i,colPartyM);
        if(cellItem->checkState()==Qt::Checked)
            str=str+"党员";
        else
            str=str+"群众";
        ui->plainTextEdit->appendPlainText(str);
    }
}
