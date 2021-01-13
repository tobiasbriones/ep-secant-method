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
