/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Monomial.h"

Monomial::Monomial(int degree, double coefficient) :
    degree(degree)
{
    if (degree < 0)
    {
        string msg = "A monomial has non-negative degree, invalid degree " + degree;
        throw runtime_error(msg);
    }
    setCoefficient(coefficient);
}

void Monomial::setCoefficient(double coefficient)
{
    this->coefficient = coefficient;
}

double Monomial::getCoefficient() const
{
    return coefficient;
}

double Monomial::eval(double x) const
{
    return coefficient * pow(x, degree);
}

string Monomial::toString(bool positive) const
{
    string sign = (coefficient < 0) ? " - " : " + ";
    string c;

    if (coefficient == 0)
    {
        return "";
    }
    if (!positive && sign == " + ")
    {
        sign = "";
    }

    if ((coefficient == -1 || coefficient == 1) && degree > 0)
    {
        c = "";
    }
    else
    {
        if (coefficient == floor(coefficient))
        {
            c = to_string(abs(coefficient));
            c = c.substr(0, c.find("."));
        }
        else
        {
            c = to_string(fabs(coefficient));
            int end = c.length() - 1;

            if (c[end] == '0')
            {
                do
                {
                    end--;
                }
                while (c[end] == '0');
                c = c.substr(0, end + 1);
            }
        }
    }
    switch (degree)
    {
        case 0:
            return sign + c;
        case 1:
            return sign + c + "x";
    }
    return sign + c + "x^" + to_string(degree);
}
