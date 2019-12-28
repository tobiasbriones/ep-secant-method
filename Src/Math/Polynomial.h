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
	const int degree;
	vector<Monomial> monomials;

public:
	Polynomial(int);

	int getDegree() const;
	void setCoefficient(int, double);
	double getCoefficient(int) const;
	double eval(double);
	string toString();
	bool isConstant() const;

};
