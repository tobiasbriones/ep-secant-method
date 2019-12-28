/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Polynomial.h"

Polynomial::Polynomial(int grade) :
	grade(grade)
{
	if (grade < 0)
	{
		string msg = "A polynomial has non-negative grade, invalid grade " + grade;
		throw runtime_error(msg);
	}
	for (int i = 0; i < grade; i++)
	{
		monomials.push_back(Monomial(i, 0));
	}
	monomials.push_back(Monomial(grade, 1));
}

int Polynomial::getGrade() const
{
	return grade;
}

void Polynomial::setCoefficient(int monomialGrade, double value)
{
	if (monomialGrade < 0 || monomialGrade > grade)
	{
		string msg = "Invalid monomial grade " + to_string(monomialGrade) + " for polynomial of grade " + to_string(grade);
		throw runtime_error(msg);
	}
	// The last monomial can't be zero as this polynomial has grade n
	// It may be zero only if it is a constant polynomial
	if (!isConstant() && monomialGrade == grade && value == 0)
	{
		string g = to_string(grade);
		string msg = "This polynomial has grade " + g + ", the monomial of grade " + g + " can't be zero.";

		throw runtime_error(msg);
	}
	monomials.at(monomialGrade).setCoefficient(value);
}

double Polynomial::getCoefficient(int monomialGrade) const
{
	return monomials.at(monomialGrade).getCoefficient();
}

double Polynomial::eval(double x)
{
	vector<Monomial>::iterator it;
	double y = 0;

	for (it = monomials.begin(); it != monomials.end(); it++)
	{
		Monomial monomial = (*it);
		y += monomial.eval(x);
	}
	return y;
}

string Polynomial::toString()
{
	vector<Monomial>::iterator it;
	string str = "";

	for (it = monomials.begin(); it != monomials.end(); it++)
	{
		str += (*it).toString();
	}
	return str;
}

bool Polynomial::isConstant() const
{
	return grade == 0;
}
