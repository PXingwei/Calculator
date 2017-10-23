#include "QCalculatorDec.h"

QCalculatorDec::QCalculatorDec()
{
    m_expression = "";
    m_result = "";
}

bool QCalculatorDec::isDigitorDot(QChar c)
{
    return ((('0' <= c) && (c <= '9')) || (c == '.'));
}

bool QCalculatorDec::isSymbol(QChar c)
{
    return (isOperator(c) || (c == '(') || (c == ')'));
}

bool QCalculatorDec::isSign(QChar c)
{
    return ((c == '+') || (c == '-'));
}

bool QCalculatorDec::isNumber(QString s)
{
    bool ret = true;

    s.toDouble(&ret);

    return ret;
}

bool QCalculatorDec::isOperator(QString s)
{
    return ((s == "+") || (s == "-") || (s == "*") || (s == "/"));
}

bool QCalculatorDec::isLeft(QString s)
{
    return (s == "(");
}

bool QCalculatorDec::isRight(QString s)
{
    return (s == ")");
}

int QCalculatorDec::priority(QString s)
{
    int ret = 0;

    if((s == "+") || (s == "-"))
    {
        ret = 1;
    }
    else if((s == "*") || (s == "/"))
    {
        ret = 2;
    }

    return ret;
}

QQueue<QString> QCalculatorDec::split(QString expression)
{
    QQueue<QString> ret;
    QString prev = "";
    QString num = "";

    for(int i=0; i<expression.length(); i++)
    {
        if(isDigitorDot(expression[i]))
        {
            num += expression[i];
            prev = expression[i];
        }
        else if(isSymbol(expression[i]))
        {

            if(!num.isEmpty())
            {
                ret.enqueue(num);
                num.clear();
            }

            if(isSign(expression[i]) && ((prev == "") || (prev == "(") || isOperator(prev)))
            {
                num += expression[i];
            }
            else
            {

                ret.enqueue(QString(expression[i]));
            }

            prev = expression[i];
        }
    }

    if(!(num.isEmpty()))
    {
         ret.enqueue(num);
    }

    return ret;
}

bool QCalculatorDec::match(QQueue<QString>& input)
{
    bool ret = true;
    QStack<QString> stack;
    for(int i=0; i<input.length(); i++)
    {
        if(isLeft(input[i]))
        {
            stack.push(input[i]);
        }
        else if(isRight(input[i]))
        {
            if(!stack.isEmpty() && isLeft(stack.top()))
            {
                stack.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }
    }

    return ret && stack.isEmpty();
}

bool QCalculatorDec::transform(QQueue<QString>& input, QQueue<QString>& output)
{
    bool ret = match(input);
    output.clear();
    QStack<QString> stack;

    while(ret && !input.isEmpty())
    {
        QString s = input.dequeue();

        if(isNumber(s))
        {
            output.enqueue(s);
        }
        else if(isOperator(s))
        {
            while(!stack.isEmpty() && priority(stack.top()) >= priority(s))
            {
                output.enqueue(stack.pop());
            }

            stack.push(s);
        }
        else if(isLeft(s))
        {
            stack.push(s);
        }
        else if(isRight(s))
        {
            while(!stack.isEmpty() && !isLeft(stack.top()))
            {
                output.enqueue(stack.pop());
            }

            if(!stack.isEmpty())
            {
                stack.pop();
            }
        }
        else
        {
            ret = false;
        }
    }

    while(!stack.isEmpty())
    {
        output.enqueue(stack.pop());
    }

    return ret;
}

QString QCalculatorDec::calculate(QQueue<QString>& exp)
{
    QString ret = "error";
    QStack<QString> stack;

    while(!exp.isEmpty())
    {
        QString e = exp.dequeue();

        if(isNumber(e))
        {
            stack.push(e);
        }
        else if(isOperator(e))
        {
            QString rightNo = stack.isEmpty() ? "" : stack.pop();
            QString leftNo = stack.isEmpty() ? "" : stack.pop();
            QString result = calculate(leftNo, e, rightNo);

            if(result != "error")
            {
                stack.push(result);
            }
            else
            {
                break;
            }
        }
    }

    if(exp.isEmpty() && (stack.size() == 1) && isNumber(stack.top()))
    {
       ret = stack.pop();
    }

    return ret;
}

QString QCalculatorDec::calculate(QString l, QString op, QString r)
{
    QString ret = "error";

    if(isNumber(l) && isNumber(r))
    {
        double lp = l.toDouble();
        double rp = r.toDouble();

        if(op == "+")
        {
            ret.sprintf("%f", lp + rp);
        }
        else if(op == "-")
        {
            ret.sprintf("%f", lp - rp);
        }
        else if(op == "*")
        {
            ret.sprintf("%f", lp * rp);
        }
        else if(op == "/")
        {
            const double delta = 0.000000000000001;
            if((-delta < rp) && (rp < delta))
            {
                ret = "error";
            }
            else
            {
               ret.sprintf("%f", lp /rp);
            }
        }
        else
        {
            ret = "error";
        }
    }

    return ret;
}

bool QCalculatorDec::expression(const QString& exp)
{
    bool ret = false;
    QQueue<QString> input;
    QQueue<QString> output;
    m_expression = exp;

    input = split(m_expression);

    if(transform(input, output))
    {
        m_result = calculate(output);
        ret = m_result != "error";
    }
    else
    {
        m_result = "error";
    }

    return ret;
}

QString QCalculatorDec::result()
{
    return m_result;
}

