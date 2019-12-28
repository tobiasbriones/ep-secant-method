/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include "SecantMethodApp.h"

const double SecantMethodApp::ERROR = pow(10, -4);
const int SecantMethodApp::THRESHOLD = 1000;

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

// --------------------------------------------- NUMERICAL METHOD APP --------------------------------------------- //
string SecantMethodApp::getName() const
{
    return "SECANT";
}

bool SecantMethodApp::gatherInput()
{
	try
	{
		n = getInt("Enter the polynomial degree: ");
		pPolynomial = new Polynomial(n);

		for (int i = 0; i <= n; i++)
		{
			double coefficient = getDouble("Enter the coefficient " + to_string(i) + ": ");

			pPolynomial->setCoefficient(i, coefficient);
		}
		cout << "Computing the roots for: P(x) = " << pPolynomial->toString() << endl << endl;
		a = getDouble("Enter a: ");
		b = getDouble("Enter b: ");

		// If polynomial is constant don't worry about checking this
		if (!pPolynomial->isConstant())
		{
			if (a == b)
			{
				throw runtime_error("a = b is not allowed, choose a < b");
			}
			if (pPolynomial->eval(a) == pPolynomial->eval(b))
			{
				throw runtime_error("P(a) = P(b) is not allowed, choose a < b such that P(a) != P(b)");
			}
		}
	}
	catch (const runtime_error & e)
	{
		printf("\n");
		printf(e.what());
		printf("\n");
		return false;
	}
	return true;
}

bool SecantMethodApp::execute()
{
	// The method doesn't apply for constant polynomials as you have to divide by zero in that case
	if (pPolynomial->isConstant())
	{
		if (pPolynomial->eval(0) == 0)
		{
			const string msg = "Every real number is a zero of the constant polynomial P(x) = " + pPolynomial->toString();
			root = 0;
			froot = 0;
			rootFound = true;

			cout << msg << endl;
		}
		else
		{
			const string msg = "The constant polynomial P(x) = " + pPolynomial->toString() + " has no roots";

			cout << msg << endl;
		}
		return true;
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

		if (iterationsNumber == THRESHOLD)
		{
			break;
		}
	}
	froot = fcurrent;
	rootFound = hasFinished;
	return true;
}

void SecantMethodApp::showResults() const
{
	printf("\n");
	printf("# of iterations: %d", iterationsNumber);
	printf("\n");
	if (rootFound)
	{
		printf("Root at x = %f", root);
		printf("\n");
		printf("P(x) = %f", froot);
	}
	else
	{
		printf("A root wasn't found");
		printf("\n");
		printf("Last iteration at x = %f", root);
		printf("\n");
		printf("P(x) = %f", froot);
	}
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
	rootFound = false;

    delete pPolynomial;
    pPolynomial = NULL;
}
