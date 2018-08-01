#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDate>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_btnSetHeader_clicked();

    void on_btnIniData_clicked();

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_btnResizeHigh_clicked();

    void on_btnResieWidth_clicked();

    void on_checkBoxEditable_clicked(bool checked);

    void on_checkBoxRowColor_clicked(bool checked);

    void on_checkBoxHeaderH_clicked(bool checked);

    void on_checkBoxHeaderV_clicked(bool checked);

    void on_radioSelectRow_clicked();

    void on_radioSelectItem_clicked();

    void on_btnSetRowCount_clicked();

    void on_pushButton_9_clicked();

private:
    //自定义单元格Type的类型 在创建单元格的item时使用
    enum CellType{
        ctName=1000,
        ctSex,
        ctBrith,
        ctNation,
        ctPartyM,
        ctScore
    };
    //各字段在表格中的列号
    enum Field{
        colName=0,
        colSex,
        colBirth,
        colNation,
        colPartyM,
        colScore
    };
    QLabel* labCellIndex;//状态栏用于显示单元格的行号 列号
    QLabel* labCellType;//状态栏用于显示单元格的类型
    QLabel* labStudID;//状态栏用于显示行号
    void createItemsARow(int rowNo,QString Name,QString Sex,QDate birth,QString Nation,bool isPM,int score);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
