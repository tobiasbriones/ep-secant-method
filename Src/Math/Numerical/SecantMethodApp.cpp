/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include "SecantMethodApp.h"

const double SecantMethodApp::ERROR = pow(10, -4);

SecantMethodApp::SecantMethodApp()
{
	pPolynomial = NULL;

    reset();
}

SecantMethodApp::~SecantMethodApp()
{
    delete pPolynomial;
    pPolynomial = NULL;
}

string SecantMethodApp::getName() const
{
    return "SECANT";
}

void SecantMethodApp::gatherInput()
{
	printf("Enter the polynomial degree\n");
	cin >> n;
	if (n < 0)
	{
		printf("The polynomial degree must be a non-negative integer");
		system("pause");
		return;
	}
	pPolynomial = new Polynomial(n);

	for (int i = 0; i <= n; i++)
	{
		double coefficient;

		printf("Enter the coefficient %d: ", i);
		cin >> coefficient;
		pPolynomial->setCoefficient(i, coefficient);
	}
	cout << "Computing the roots for: " << pPolynomial->toString() << endl;
	printf("Enter a:\n");
	cin >> a;
	printf("Enter b:\n");
	cin >> b;
}

void SecantMethodApp::execute()
{
	// The method doesn't apply for constant polynomials as you have to divide by zero in that case
	if (pPolynomial->isConstant())
	{
		if (pPolynomial->eval(0) == 0)
		{

		}
	}
	double previousPrevious = a;
	double previous = b;
	double current;
	double fcurrent;
	double errorFactor = (1 / ERROR) / 10;
	bool hasFinished = false;

	while (!hasFinished)
	{
		double fpreviousPrevious = pPolynomial->eval(previousPrevious);
		double fprevious = pPolynomial->eval(previous);

		current = previousPrevious - fpreviousPrevious * ((previous - previousPrevious) / (fprevious - fpreviousPrevious));
		fcurrent = pPolynomial->eval(current);
		previousPrevious = previous;
		previous = current;
		hasFinished = (fabs(fcurrent) * errorFactor) < 1;
		iterationsNumber++;
	}
	froot = fcurrent;
}

void SecantMethodApp::showResults() const
{
	printf("\n");
	printf("# iterations: %d", iterationsNumber);
	printf("\n");
	printf("Root at x = %f", root);
	printf("\n");
	printf("P(x) = %f", froot);
	printf("\n");
}

void SecantMethodApp::reset()
{
    n = 0;
    a = 0;
    b = 0;
    iterationsNumber = 0;
    root = 0;
    froot = 0;

    delete pPolynomial;
    pPolynomial = NULL;
}
