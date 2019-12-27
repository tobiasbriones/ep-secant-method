/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include<iostream>
#include<stdio.h>
#include<string>
#include<sstream>
#include<vector>
#include<cmath>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::to_string;
using std::stringstream;
using std::vector;

class Monomial
{

public:
	double coefficient;
	int grade;

	Monomial(double coefficient, int grade)
	{
		this->coefficient = coefficient;
		this->grade = grade;
	}

	string toString()
	{
		string sign = (coefficient < 0) ? " - " : " + ";
		string c;

		if (coefficient == floor(coefficient))
		{
			c = to_string(abs(coefficient));
		}
		else
		{
			c = to_string(fabs(coefficient));
		}
		switch (grade)
		{
		case 0: return c;
		case 1: return sign + c + "x";
		}
		return sign + c + "x^" + to_string(grade);
	}

	double getCoefficient()
	{
		return coefficient;
	}

	double eval(double x)
	{
		return coefficient * pow(x, grade);
	}

};

class Polynomial
{

private:
	int grade;
	vector<Monomial> monomials;

public:
	Polynomial(int grade)
	{
		this->grade = grade;
	}

	int getGrade()
	{
		return grade;
	}

	void dump()
	{
		vector<Monomial>::iterator it;
		int i = 0;

		for (it = monomials.begin(); it != monomials.end(); it++, i++)
		{
			cout << (*it).toString();
		}
		cout << endl;
	}

	void setCoefficient(int c, double value)
	{
		Monomial monomial(value, c);

		monomials.insert(monomials.begin() + c, monomial);
	}

	double getCoefficient(int c)
	{
		return monomials.at(c).getCoefficient();
	}

	double eval(double x)
	{
		vector<Monomial>::iterator it;
		int i = 0;
		double y = 0;

		for (it = monomials.begin(); it != monomials.end(); it++, i++)
		{
			y += (*it).eval(x);
		}
		return y;
	}

};

double getRootBySecantMethod(double a, double b, Polynomial& polynomial, double error, double& froot, int& i)
{
	if (error == 0)
	{
		cout << "El error no puede ser cero" << endl;
		return 0;
	}
	if (polynomial.getGrade() == 0)
	{
		return polynomial.eval(a);
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
	double error = pow(10, -4);
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
	printf("Calculando las raices para: ");
	polynomial.dump();
	printf("Ingresar a:\n");
	cin >> a;
	printf("Ingresar b:\n");
	cin >> b;
	int i = 0;
	double froot = -1;
	double root = getRootBySecantMethod(a, b, polynomial, error, froot, i);

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
