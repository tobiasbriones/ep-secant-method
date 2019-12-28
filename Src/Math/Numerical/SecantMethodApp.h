/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <cmath>
#include "NumericalMethodApp.h"
#include "../Polynomial.h"

class SecantMethodApp : public NumericalMethodApp
{

private:
    static const double ERROR;
    int n;
    double a;
    double b;
    Polynomial* pPolynomial;
    int iterationsNumber;
    double root;
    double froot;

protected:
    string getName() const;
    void gatherInput();
    void execute();
    void showResults() const;
    void reset();
    
public:
    SecantMethodApp();
    ~SecantMethodApp();

};
