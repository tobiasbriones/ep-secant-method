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
	const int degree;
	double coefficient;

public:
	Monomial(int, double);

	void setCoefficient(double);
	double getCoefficient() const;
	double eval(double) const;
	string toString(bool = true) const;

};
