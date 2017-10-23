#ifndef _ICALCULATOR_H_
#define _ICALCULATOR_H_
#include <QString>

class ICalculator
{
public:
    virtual QString result() = 0;
    virtual bool expression(const QString& exp) = 0;
};

#endif // ICALCULATOR_H
