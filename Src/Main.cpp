/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <iostream>
#include <cmath>
#include "Math/Polynomial.h"

using std::cout;
using std::endl;
using std::cin;

const int ERROR = pow(10, -4);

double getRootBySecantMethod(double a, double b, Polynomial& polynomial, double& froot, int& i)
{
	// The method doesn't apply for constant polynomials as you have to divide by zero in that case
	if (polynomial.isConstant())
	{
		if (polynomial.eval(0) == 0)
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
		double fpreviousPrevious = polynomial.eval(previousPrevious);
		double fprevious = polynomial.eval(previous);

		current = previousPrevious - fpreviousPrevious * ((previous - previousPrevious) / (fprevious - fpreviousPrevious));
		fcurrent = polynomial.eval(current);
		previousPrevious = previous;
		previous = current;
		hasFinished = (fabs(fcurrent) * errorFactor) < 1;
		i++;
	}
	froot = fcurrent;
	return current;
}

void run()
{
	int n;
	double a;
	double b;

	printf("Enter the polynomial degree\n");
	cin >> n;
	if (n < 0)
	{
		printf("The polynomial degree must be a non-negative integer");
		system("pause");
		run();
		return;
	}
	Polynomial polynomial(n);

	for (int i = 0; i <= n; i++)
	{
		double coefficient;

		printf("Enter the coefficient %d: ", i);
		cin >> coefficient;
		polynomial.setCoefficient(i, coefficient);
	}
	cout << "Computing the roots for: " << polynomial.toString() << endl;
	printf("Enter a:\n");
	cin >> a;
	printf("Enter b:\n");
	cin >> b;
	int i = 0;
	double froot = -1;
	double root = getRootBySecantMethod(a, b, polynomial, froot, i);

	printf("\n");
	printf("# iterations: %d", i);
	printf("\n");
	printf("Root at x = %f", root);
	printf("\n");
	printf("P(x) = %f", froot);
}

int main()
{
	run();
	return 0;
}
