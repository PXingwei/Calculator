#ifndef _QCALCULATORDEC_H_
#define _QCALCULATORDEC_H_

#include <QString>
#include <QQueue>
#include <QStack>
#include <QDebug>
#include "ICalculator.h"

class QCalculatorDec : public ICalculator
{
protected:
    QString m_expression;
    QString m_result;

    bool isDigitorDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);

    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);

    QQueue<QString> split(QString expression);
    bool transform(QQueue<QString>& input, QQueue<QString>& output);
    bool match(QQueue<QString>& input);
    QString calculate(QQueue<QString>& exp);
    QString calculate(QString l, QString op, QString r);

public:
    QCalculatorDec();
    QString result();
    bool expression(const QString& exp);
};

#endif // QCALCULATORDEC_H
