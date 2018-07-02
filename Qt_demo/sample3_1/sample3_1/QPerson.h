#ifndef QPERSON_H
#define QPERSON_H
#include<QObject>
#include<QString>

class QPerson : public QObject
{
    Q_OBJECT //有这个宏就可以使用qt元对象系统支持
    //使用CLASS_INFO定义类的附加信息
    Q_CLASSINFO("author","duyong")
    Q_CLASSINFO("company","UPC")
    Q_CLASSINFO("version","1.0.0")
    //使用PROPERTY定义类的属性
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int score MEMBER m_score)
private:
    int m_age = 10;
    QString m_name;
    int m_score = 79;
public:
    explicit QPerson(QString fName,QObject *parent = 0);
    int age();
    void setAge(int value);
    void incAge();

signals:
    void ageChanged(int value);
public slots:
};

#endif // QPERSON_H
