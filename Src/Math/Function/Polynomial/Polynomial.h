/*
 * Copyright (c) 2019 Tobias Briones. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Example Project: Secant Method.
 *
 * This source code is licensed under the MIT License found in the
 * LICENSE file in the root directory of this source tree or at
 * https://opensource.org/licenses/MIT.
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
/// Defines a polynomial. It assigns n + 1 monomials for an n-degree polynomial.
/// </summary>
class Polynomial
{

private:
    const int degree;
    vector <Monomial> monomials;

public:
    Polynomial(int);

    int getDegree() const;

    void setCoefficient(int, double);

    void set(vector<double>);

    double getCoefficient(int) const;

    double eval(double);

    string toString();

    bool isConstant() const;
};
