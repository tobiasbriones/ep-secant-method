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
    static const int THRESHOLD;
    int n;
    double a;
    double b;
    Polynomial* pPolynomial;
    int iterationsNumber;
    double root;
    double froot;
    bool rootFound;

    static double roundPrecision(double value, double error);

protected:
    string getName() const;
    bool gatherInput();
    bool execute();
    void showResults() const;
    void reset();
    
public:
    SecantMethodApp();
    ~SecantMethodApp();

    static double compute(Polynomial&, double, double, double, int, bool&, int&, double&);

};
