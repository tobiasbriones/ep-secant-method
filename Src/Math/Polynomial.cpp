/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Polynomial.h"

Polynomial::Polynomial(int degree) :
	degree(degree)
{
	if (degree < 0)
	{
		string msg = "A polynomial has non-negative degree, invalid degree " + to_string(degree);
		throw runtime_error(msg);
	}
	for (int i = 0; i < degree; i++)
	{
		monomials.push_back(Monomial(i, 0));
	}
	monomials.push_back(Monomial(degree, 1));
}

int Polynomial::getDegree() const
{
	return degree;
}

void Polynomial::setCoefficient(int monomialDegree, double value)
{
	if (monomialDegree < 0 || monomialDegree > degree)
	{
		string msg = "Invalid monomial degree " + to_string(monomialDegree) + " for polynomial of degree " + to_string(degree);
		throw runtime_error(msg);
	}
	// The last monomial can't be zero as this polynomial has grade n
	// It may be zero only if it is a constant polynomial
	if (!isConstant() && monomialDegree == degree && value == 0)
	{
		string g = to_string(degree);
		string msg = "This polynomial has degree " + g + ", the monomial of degree " + g + " can't be zero.";

		throw runtime_error(msg);
	}
	monomials.at(monomialDegree).setCoefficient(value);
}

double Polynomial::getCoefficient(int monomialDegree) const
{
	return monomials.at(monomialDegree).getCoefficient();
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
	bool positive = false;

	for (it = monomials.begin(); it != monomials.end(); it++)
	{
		str += (*it).toString(positive);

		if (str != "")
		{
			positive = true;
		}
	}
	return str;
}

bool Polynomial::isConstant() const
{
	return degree == 0;
}
