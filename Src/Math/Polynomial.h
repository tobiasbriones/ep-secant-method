/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include "Monomial.h"

using std::runtime_error;
using std::string;
using std::to_string;
using std::vector;

/// <summary>
/// Defines a polynomial. It assigns n monomials for a n-grade polynomial.
/// </summary>
class Polynomial
{

private:
	const int grade;
	vector<Monomial> monomials;

public:
	Polynomial(int grade) :
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

	int getGrade() const
	{
		return grade;
	}

	void setCoefficient(int grade, double value)
	{
		if (grade < 0 || grade >= monomials.size())
		{
			string msg = "Invalid monomial grade " + to_string(grade) + " for polynomial of grade " + to_string(this->grade);
			throw runtime_error(msg);
		}
		// The last monomial can't be zero as this polynomial has grade n
		// It may be zero only if it is a constant polynomial
		if (!isConstant() && grade == this->grade && value == 0)
		{
			string g = to_string(this->grade);
			string msg = "This polynomial has grade " + g + ", the monomial of grade " + g + " can't be zero.";

			throw runtime_error(msg);
		}
		monomials.at(grade).setCoefficient(value);
	}

	double getCoefficient(int c) const
	{
		return monomials.at(c).getCoefficient();
	}

	double eval(double x)
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

	string toString()
	{
		vector<Monomial>::iterator it;
		string str = "";

		for (it = monomials.begin(); it != monomials.end(); it++)
		{
			str += (*it).toString();
		}
		return str;
	}

	bool isConstant() const
	{
		return grade == 0;
	}

};
