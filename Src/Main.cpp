/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdio.h>

using std::cout;
using std::endl;
using std::cin;
using std::runtime_error;
using std::string;
using std::to_string;
using std::stringstream;
using std::vector;

/// <summary>
/// Defines a monomial.
/// </summary>
class Monomial
{

public:
	const int grade;
	double coefficient;

	Monomial(int grade, double coefficient) :
		grade(grade)
	{
		if (grade < 0)
		{
			string msg = "A monomial has non-negative grade, invalid grade " + grade;
			throw runtime_error(msg);
		}
		setCoefficient(coefficient);
	}

	void setCoefficient(double coefficient)
	{
		this->coefficient = coefficient;
	}

	double getCoefficient() const
	{
		return coefficient;
	}

	double eval(double x) const
	{
		return coefficient * pow(x, grade);
	}

	string toString() const
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
		case 0: return sign + c;
		case 1: return sign + c + "x";
		}
		return sign + c + "x^" + to_string(grade);
	}

};

/// <summary>
/// Defines a polynomial. It assigns n monomials for a n-grade polynomial.
/// </summary>
class Polynomial
{

private:
	const int grade;
	vector<Monomial> monomials;

public:
	Polynomial(int grade) :
		grade(grade)
	{
		if (grade < 0)
		{
			string msg = "A polynomial has non-negative grade, invalid grade " + grade;
			throw runtime_error(msg);
		}
		for (int i = 0; i < grade; i++)
		{
			monomials.push_back(Monomial(i, 0));
		}
		monomials.push_back(Monomial(grade, 1));
	}

	int getGrade() const
	{
		return grade;
	}

	void setCoefficient(int grade, double value)
	{
		if (grade < 0 || grade >= monomials.size())
		{
			string msg = "Invalid monomial grade " + to_string(grade) + " for polynomial of grade " + to_string(this->grade);
			throw runtime_error(msg);
		}
		// The last monomial can't be zero as this polynomial has grade n
		// It may be zero only if it is a constant polynomial
		if (!isConstant() && grade == this->grade && value == 0)
		{
			string g = to_string(this->grade);
			string msg = "This polynomial has grade " + g + ", the monomial of grade " + g + " can't be zero.";

			throw runtime_error(msg);
		}
		monomials.at(grade).setCoefficient(value);
	}

	double getCoefficient(int c) const
	{
		return monomials.at(c).getCoefficient();
	}

	double eval(double x)
	{
		vector<Monomial>::iterator it;
		double y = 0;

		for (it = monomials.begin(); it != monomials.end(); it++)
		{
			Monomial monomial = (*it);
			y += monomial.eval(x);
		}
		return y;
	}

	string toString()
	{
		vector<Monomial>::iterator it;
		string str = "";

		for (it = monomials.begin(); it != monomials.end(); it++)
		{
			str += (*it).toString();
		}
		return str;
	}

	bool isConstant() const
	{
		return grade == 0;
	}

};

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
	cout << "Calculando las raices para: " << polynomial.toString() << endl;
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
