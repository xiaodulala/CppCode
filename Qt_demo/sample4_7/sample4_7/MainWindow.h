#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //初始化树
    void initTree();
    //添加目录节点
    void addFolderItem(QTreeWidgetItem* parItem,QString dirName);
    //提取目录名称
    QString getFinalFolderName(const QString& fullPathName);
    //添加图片节点
    void addImageItem(QTreeWidgetItem *parItem,QString aFilename);
    //显示一个图片节点的图片
    void displayImage(QTreeWidgetItem* item);
    //遍历改变节点标题
    void changeItemCaption(QTreeWidgetItem* item);
private slots:

    void on_actAddFiles_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actDeleteItem_triggered();

    void on_actScanItems_triggered();

    void on_actAddFloder_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomFith_triggered();



    void on_actZoomFitW_triggered();

    void on_actZoomRealSize_triggered();

    void on_actDockVisible_toggled(bool arg1);

    void on_actDockFloat_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    //枚举类型treeItemType 创建节点时用作type参数 自定义类型必须大于1000
    enum treeItemType{itTopItem=1001,itGroupItem,itImageItem};
    //目录树列的编号
    enum treeColNum{colItem=0,colItemType=1};//0第一列 1第二列
    QLabel *LabFileName;//用于状态栏显示文件名
    QPixmap curPixmap;//当前的图片
    float pixRatio; //当前缩放比例
private:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
