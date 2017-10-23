#include "Qcalculatorui.h"

QCalculatorUI::QCalculatorUI()
    : QWidget(NULL, Qt::WindowCloseButtonHint)
{
    m_cal = NULL;
}

void QCalculatorUI::onButtonClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    if(btn != NULL)
    {
        QString ClickText = btn->text();

        if(ClickText == "<-")
        {
            QString text = m_edit->text();
            if(text.length() > 0)
            {
                text.remove(text.length()-1, 1);
                m_edit->setText(text);
            }
        }
        else if(ClickText == "c")
        {
            m_edit->setText("");
        }
        else if(ClickText == "=")
        {
            if(m_cal != NULL)
            {
                m_cal->expression(m_edit->text());
                m_edit->setText(m_cal->result());
            }
        }
        else
        {
            QString text = m_edit->text() + ClickText;
            m_edit->setText(text);
        }
    }
}

bool QCalculatorUI::construct()
{
    bool ret = true;

    const char* str[20] = {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "c",
    };

    m_edit = new QLineEdit(this);

    if(m_edit != NULL)
    {
        m_edit->move(10, 10);
        m_edit->resize(240, 30);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);
    }
    else
    {
        ret = false;
    }

    for(int i=0; (i<4) && ret; i++)
    {
        for(int j=0; (j<5) && ret; j++)
        {
            m_btn[i*5+j] = new QPushButton(this);
            if(m_btn[i*5+j] != NULL)
            {
                m_btn[i*5+j]->resize(40, 40);
                m_btn[i*5+j]->move(10+50*j, 50+50*i);
                m_btn[i*5+j]->setText(str[i*5+j]);
                connect(m_btn[i*5+j], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
            }
            else
            {
                ret = false;
            }
        }
    }

    return ret;
}

void QCalculatorUI::show()
{
    QWidget::show();
    setFixedSize(this->width(), this->height());
}

QCalculatorUI* QCalculatorUI::newInstace()
{
    QCalculatorUI* ret = new QCalculatorUI();

    if((ret == NULL) || !(ret->construct()))
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void QCalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}

ICalculator* QCalculatorUI::getCalculator(void)
{
    return m_cal;
}

QCalculatorUI::~QCalculatorUI()
{
    
}
