#ifndef _QCALCULATOR_H_
#define _QCALCULATOR_H_
#include "Qcalculatorui.h"
#include "QCalculatorDec.h"

class QCalculator
{
private:
    QCalculatorUI* m_ui;
    QCalculatorDec m_dec;

    QCalculator();
    bool construct();

public:
    static QCalculator* newInstance();
    void show();

    ~QCalculator();
};

#endif // QCALCULATOR_H
