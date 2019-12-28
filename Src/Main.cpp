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

double getRootBySecantMethod(double a, double b, Polynomial& polynomial, double error, double& froot, int& i)
{
	if (error == 0)
	{
		cout << "El error no puede ser cero" << endl;
		return 0;
	}
	// The method doesn't apply for constant polynomials as you have to divide by zero in that case
	if (polynomial.isConstant())
	{
		if (polynomial.eval(0) == 0)
		{
			
		}
	}
	double previusPrevius = a;
	double previus = b;
	double current;
	double fcurrent;
	double errorFactor = (1 / error) / 10;
	bool hasFinished = false;

	while (!hasFinished)
	{
		double fpreviusPrevius = polynomial.eval(previusPrevius);
		double fprevius = polynomial.eval(previus);

		current = previusPrevius - fpreviusPrevius * ((previus - previusPrevius) / (fprevius - fpreviusPrevius));
		fcurrent = polynomial.eval(current);
		previusPrevius = previus;
		previus = current;
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

	printf("Ingresar grado del polinomio (0-5)\n");
	cin >> n;
	if (n < 0 || n > 5)
	{
		printf("El grado del polinomio debe ser de 0-5");
		system("pause");
		run();
		return;
	}
	Polynomial polynomial(n);

	for (int i = 0; i <= n; i++)
	{
		double coefficient;

		printf("Coeficiente %d: ", i);
		cin >> coefficient;
		polynomial.setCoefficient(i, coefficient);
	}
	cout << "Calculando las raices para: " << polynomial.toString() << endl;
	printf("Ingresar a:\n");
	cin >> a;
	printf("Ingresar b:\n");
	cin >> b;
	int i = 0;
	double froot = -1;
	double root = getRootBySecantMethod(a, b, polynomial, ERROR, froot, i);

	printf("\n");
	printf("Iteraciones: %d", i);
	printf("\n");
	printf("Raiz en x = %f", root);
	printf("\n");
	printf("P(x) = %f", froot);
}

int main()
{
	run();
	return 0;
}
