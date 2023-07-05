#include "calc.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSizePolicy>
#include <QVBoxLayout>

Calc::Calc(QWidget* parent) : QWidget(parent)
{
    // 获取字体QFont
    QFont font = this->font();
    font.setPixelSize(30);
    this->setFont(font);

    // 保存键盘值
    QString keys = "789-456*123/0.+=";
    QVBoxLayout* vbox = new QVBoxLayout();

    QSizePolicy qsPolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    for (int i = 0; i < 4; i++)
    {
        QHBoxLayout* hbox = new QHBoxLayout();
        for (int j = 0; j < 4; j++)
        {
            buttons[i * 4 + j] = new QToolButton(this);
            // 设置文本
            buttons[i * 4 + j]->setText(keys.mid(i * 4 + j, 1));
            hbox->addWidget(buttons[i * 4 + j]);

            // 策略设置
            buttons[i * 4 + j]->setSizePolicy(qsPolicy);

            // 把按钮触发信号关联槽函数
            connect(buttons[i * 4 + j], SIGNAL(clicked(bool)), this, SLOT(buttons_chick()));
        }
        // 把水平布局管理器添加到垂直布局管理器中
        vbox->addLayout(hbox);
    }

    // 创建一个输入框
    edit = new QLineEdit(this);
    edit->setSizePolicy(qsPolicy);
    edit->setMaximumHeight(60);
    edit->setAlignment(Qt::AlignRight);

    QVBoxLayout* allVbox = new QVBoxLayout(this);
    allVbox->addWidget(edit);
    allVbox->addLayout(vbox);

    // 初始化
    firstNumber.clear();
    secondNumber.clear();
    calcflag = 0;
}

Calc::~Calc() {}

void Calc::input_data(QString str)
{
    if (calcflag == 0)
    {
        firstNumber.append(str);
        edit->setText(firstNumber);
    }
    else
    {
        secondNumber.append(str);
        edit->setText(secondNumber);
    }
}

void Calc::buttons_chick()
{
    // 通过信号发送者获取按钮对象
    QToolButton* button = (QToolButton*)sender();
    QString str = button->text();
    QString datastr = ".0123456789";
    QStringList typestr;
    typestr << "+"
            << "-"
            << "*"
            << "/";
    if (datastr.indexOf(str) >= 0)  // 获取按键值
    {
        input_data(str);  // 输入数据
    }
    else if (typestr.indexOf(str) >= 0)
    {
        calcflag = typestr.indexOf(str) + 1;  // 获取运算符号type
    }
    else  //=
    {
        double result = 0.0;
        switch (calcflag)
        {
            case 1: result = firstNumber.toDouble() + secondNumber.toDouble(); break;
            case 2: result = firstNumber.toDouble() - secondNumber.toDouble(); break;
            case 3: result = firstNumber.toDouble() * secondNumber.toDouble(); break;
            case 4: result = firstNumber.toDouble() / secondNumber.toDouble(); break;
            default: break;
        }
        edit->setText(QString::number(result));
        calcflag = 0;
        firstNumber.clear();
        secondNumber.clear();
    }
}
