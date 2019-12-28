/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Monomial.h"

Monomial::Monomial(int grade, double coefficient) :
	grade(grade)
{
	if (grade < 0)
	{
		string msg = "A monomial has non-negative grade, invalid grade " + grade;
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
	return coefficient * pow(x, grade);
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
	switch (grade)
	{
	case 0: return sign + c;
	case 1: return sign + c + "x";
	}
	return sign + c + "x^" + to_string(grade);
}
