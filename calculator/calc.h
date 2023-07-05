#ifndef CALC_H
#define CALC_H

#include <QLineEdit>
#include <QToolButton>
#include <QWidget>

class Calc : public QWidget
{
    Q_OBJECT
public:
    explicit Calc(QWidget* parent = 0);
    ~Calc();
    void input_data(QString str);

protected slots:
    void buttons_chick();  // 按键槽函数

private:
    QToolButton* buttons[16];  // 按钮数组
    QLineEdit* edit;           // 输入框
    QString firstNumber;       // 记录输入第一个数值
    QString secondNumber;      // 记录输入第一个数值
    int calcflag;              // 1-add， 2-sub, 3-mul, 4-div
};

#endif  // CALC_H
