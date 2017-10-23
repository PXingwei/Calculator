#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include "ICalculator.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT

private slots:
    void onButtonClicked();

private:
    QPushButton* m_btn[20];
    QLineEdit* m_edit;
    ICalculator* m_cal;

    QCalculatorUI();
    bool construct();

public:
    static QCalculatorUI* newInstace();
    void show();
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator(void);
    ~QCalculatorUI();
};

#endif // QCALCULATORUI_H
