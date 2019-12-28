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

string Monomial::toString() const
{
	string sign = (coefficient < 0) ? " - " : " + ";
	string c;

	if (coefficient == floor(coefficient))
	{
		c = to_string(abs(coefficient));
	}
	else
	{
		c = to_string(fabs(coefficient));
	}
	switch (degree)
	{
	case 0: return sign + c;
	case 1: return sign + c + "x";
	}
	return sign + c + "x^" + to_string(degree);
}
