/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;
using std::to_string;

/// <summary>
/// Defines a monomial.
/// </summary>
class Monomial
{

private:
	const int grade;
	double coefficient;

public:
	Monomial(int grade, double coefficient);

	void setCoefficient(double coefficient);
	double getCoefficient() const;
	double eval(double x) const;
	string toString() const;

};
