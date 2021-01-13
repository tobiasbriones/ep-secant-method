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

#include "SecantTest.h"

void Result::set(double root, double froot, int i, bool wasFound)
{
    this->root = root;
    this->froot = froot;
    this->iterations = i;
    this->wasFound = wasFound;
}

bool comparePrecision(double value1, double value2)
{
    return abs(value1 - value2) < ERROR;
}

void testPolynomial(Polynomial& p, double a, double b, Result expected, int& passedCount, int& failedCount)
{
    bool rootFound;
    int i;
    double froot;
    double root = SecantMethodApp::compute(p, a, b, ERROR, THRESHOLD, rootFound, i, froot);
    bool passed = true;

    printf("Testing polynomial...\n");

    // If a root was found but there is actually no root for this call of the algorithm or
    // if there is a root but a root was not found by the algorithm
    // then the test is already failed
    if (rootFound != expected.wasFound)
    {
        printf(
            "Different outcome, root found is %s but %s was expected\n",
            rootFound ? "true" : "false",
            expected.wasFound ? "true" : "false"
        );
        passed = false;
        printf("It = %d\n", i);
    }

    if (rootFound)
    {
        bool passedRoot = comparePrecision(root, expected.root);
        bool passedFRoot = comparePrecision(froot, expected.froot);
        bool passedIterations = i == expected.iterations;
        passed &= passedRoot && passedFRoot && passedIterations;

        if (!passed)
        {
            if (!passedRoot)
            {
                printf("Roots didn't pass, found: x = %f, expected x = %f\n", root, expected.root);
            }
            if (!passedFRoot)
            {
                printf("Images didn't pass, found P(x) = %f, expected P(x) = %f\n", froot, expected.froot);
            }
            if (!passedIterations)
            {
                printf(
                    "Number of iterations didn't pass, it had %d iterations, expected %d iterations\n",
                    i,
                    expected.iterations
                );
            }
        }
    }

    printf("Computation error was: %f, threshold: %d\n", ERROR, THRESHOLD);
    if (passed)
    {
        passedCount++;

        if (rootFound)
        {
            printf(
                "Root at x = %f with P(x) = %f and %d iterations, with a = %f and b = %f\n",
                root,
                froot,
                i,
                a,
                b
            );
        }
        else
        {
            printf(
                "A root wasn't found. Finished with x = %f with P(x) = %f and %d iterations\n",
                root,
                froot,
                i
            );
        }
        printf("Test for P(x) = %s PASSED!\n", p.toString().c_str());
    }
    else
    {
        failedCount++;

        printf("Test for P(x) = %s FAILED\n", p.toString().c_str());
    }
    printf("\n");
    printf("\n");
}

void testForConstantPolynomials(int& passedCount, int& failedCount)
{
    Result expected;
    Polynomial p(0);

    printf("                   TESTING FOR CONSTANT POLYNOMIALS                   ");
    printf("\n");

    // P(x) = -20
    p.setCoefficient(0, -20);
    expected.set(0, 0, 0, false);
    testPolynomial(p, -1, 1, expected, passedCount, failedCount);

    // P(x) = -1
    p.setCoefficient(0, -1);
    expected.set(0, 0, 0, false);
    testPolynomial(p, -1, 1, expected, passedCount, failedCount);

    // P(x) = 0
    p.setCoefficient(0, 0);
    expected.set(0, 0, 0, true);
    testPolynomial(p, -1, 1, expected, passedCount, failedCount);

    // P(x) = 1
    p.setCoefficient(0, 1);
    expected.set(0, 0, 0, false);
    testPolynomial(p, -1, 1, expected, passedCount, failedCount);

    // P(x) = 20
    p.setCoefficient(0, 20);
    expected.set(0, 0, 0, false);
    testPolynomial(p, -1, 1, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void testForDegreeOnePolynomial(int& passedCount, int& failedCount)
{
    Result expected;
    Polynomial p(1);

    printf("                  TESTING FOR DEGREE ONE POLYNOMIALS                  ");
    printf("\n");

    // P(x) = x
    p.set({0, 1});
    expected.set(0, 0, 1);
    testPolynomial(p, -1, 1, expected, passedCount, failedCount);

    // P(x) = -1 + x
    p.set({-1, 1});
    expected.set(1, 0, 1);
    testPolynomial(p, -5, 5, expected, passedCount, failedCount);

    // P(x) = 1 + x
    p.set({1, 1});
    expected.set(-1, 0, 1);
    testPolynomial(p, -5, 5, expected, passedCount, failedCount);

    // P(x) = 10 - 25.82x
    p.set({10, -25.82});
    expected.set(0.3873, -0.0001, 1);
    testPolynomial(p, -5, 5, expected, passedCount, failedCount);

    // P(x) = -100 + 2.25x
    p.set({-100, 2.25});
    expected.set(44.4444, -0.0001, 1);
    testPolynomial(p, -5, 5, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void testForConstantMonomialZero(int& passedCount, int& failedCount)
{
    Result expected;
    Polynomial p1(4);
    Polynomial p2(10);

    printf("            TESTING FOR ZERO CONSTANT MONOMIAL POLYNOMIALS            ");
    printf("\n");

    // P(x) = 5x - 100x^2 + 3.60x^3 + 5x^4
    p1.set({0, 5, -100, 3.60, 5});
    expected.set(-4.8695, -0.0327, 14);
    testPolynomial(p1, -5, 5, expected, passedCount, failedCount);

    // P(x) = 5x - 100x^2 + 3.60x^3 + 5x^4 (p1 again)
    p1.set({0, 5, -100, 3.60, 5});
    expected.set(0.0501, 0, 13);
    testPolynomial(p1, -2, 2, expected, passedCount, failedCount);

    // P(x) = 10x^2 + 8.64x^4 - 50x^5 + 4x^9 + 11.2x^10
    p2.set({0, 0, 10, 0, 8.64, -50, 0, 0, 0, 4, 11.2});
    expected.set(1.2068, 0.0026, 28);
    testPolynomial(p2, -5, 5, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void testForPolynomialsWithDecimals(int& passedCount, int& failedCount)
{

    Result expected;
    Polynomial p1(7);

    printf("                 TESTING FOR POLYNOMIALS WITH DECIMALS                ");
    printf("\n");

    // P(x) = -0.0094 - 5x^2 + 0.025x^3 + 0.325x^5 + 54.0223x^6 + 211.3541x^7
    p1.set({-0.0094, 0, -5, 0.025, 0, 0.325, 54.0223, 211.3541});
    expected.set(0.4311, -0.0002, 9);
    testPolynomial(p1, 0.3, 0.5, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void testForNonRootPolynomials(int& passedCount, int& failedCount)
{
    Result expected;
    Polynomial p1(4);
    Polynomial p2(2);

    printf("                 TESTING FOR POLYNOMIALS WITH NO ROOTS                ");
    printf("\n");

    // P(x) = 100 + 5x^3 + 500x^4
    p1.set({100, 0, 0, 5, 500});
    expected.set(0, 0, THRESHOLD, false);
    testPolynomial(p1, -5, 5, expected, passedCount, failedCount);

    // P(x) = -0.8 + 0.33x + 2.3584x^2 - 3.3054x^4
    p1.set({-0.8, 0.33, 2.3584, 0, -3.25});
    expected.set(0, 0, THRESHOLD, false);
    testPolynomial(p1, -5, 5, expected, passedCount, failedCount);

    // P(x) = 5 + 2x^2
    p2.set({5, 0, 2});
    expected.set(0, 0, THRESHOLD, false);
    testPolynomial(p2, -5, 5, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void testForHugePolynomials(int& passedCount, int& failedCount)
{
    Result expected;
    Polynomial p(20);

    printf("                     TESTING FOR HUGE POLYNOMIALS                     ");
    printf("\n");

    // P(x) = 5 + 23.2x - 85x^2 - 0.21x^3 + 50x^4 - 0.24x^7 + 54.35x^8 + 9x^9 - 45.5x^10 - 25x^11 + 2.25x^14
    //       - 55.254x^15 - 54x^17 + 5.35x^18 + 2.3254x^19 - 0.025x^20
    p.set(
        {5, 23.2, -85, -0.21, 50, 0, 0, -0.24, 54.35, 9, -45.5, -25, 0, 0, 2.25, -55.254, 0, -54, 5.35, 2.3254, -0.025}
    );
    expected.set(0.4599, -0.0008, 3);
    testPolynomial(p, 0.3, 0.5, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void runAllTests()
{
    int testsPassed = 0;
    int testsFailed = 0;

    testForConstantPolynomials(testsPassed, testsFailed);
    testForDegreeOnePolynomial(testsPassed, testsFailed);
    testForConstantMonomialZero(testsPassed, testsFailed);
    testForPolynomialsWithDecimals(testsPassed, testsFailed);
    testForNonRootPolynomials(testsPassed, testsFailed);
    testForHugePolynomials(testsPassed, testsFailed);
    printf("\n");
    printf(
        "%d Tests completed. Succeeded tests: %d, Failed tests: %d",
        testsPassed + testsFailed,
        testsPassed,
        testsFailed
    );
    printf("\n");
    printf("\n");
}
