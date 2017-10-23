#include "Qcalculator.h"

QCalculator::QCalculator()
{
}

bool QCalculator::construct()
{
    m_ui = QCalculatorUI::newInstace();

    if(m_ui != NULL)
    {
        m_ui->setCalculator(&m_dec);
    }

    return (m_ui != NULL);
}

QCalculator* QCalculator::newInstance()
{
    QCalculator* ret = new QCalculator();

    if((ret == NULL) || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void QCalculator::show()
{
    m_ui->show();
}

QCalculator::~QCalculator()
{
    delete m_ui;
}
