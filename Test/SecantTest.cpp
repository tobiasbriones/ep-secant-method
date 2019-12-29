/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
    double root = SecantMethodApp::compute(p, a, b, ERROR, THRESHOLD, rootFound, i);
    double froot = p.eval(root);
    bool passed = true;

    printf("Testing polynomial...\n");

    // If a root was found but there is actually no root for this call of the algorithm or
    // if there is a root but a root was not found by the algorithm
    // then the test is already failed
    if (rootFound != expected.wasFound)
    {
        printf("Different outcome, root found is %s but %s was expected\n", rootFound ? "true" : "false", expected.wasFound ? "true" : "false");
        passed = false;
    }

    // If a root was successfully found then test the results
    if (rootFound)
    {
        bool passedRoot = comparePrecision(root, expected.root);
        bool passedFRoot = comparePrecision(froot, expected.froot);
        bool passedIterations = i == expected.iterations;
        passed &= passedRoot && passedFRoot && passedIterations;

        // If it didn't pass the previous tests, show the information
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
                printf("Number of iterations didn't pass, it had %d iterations, expected %d iterations\n", i, expected.iterations);
            }
        }
    }

    printf("Computation error was: %f, threshold: %d\n", ERROR, THRESHOLD);
    if (passed)
    {
        passedCount++;

        if (rootFound)
        {
            printf("Root at x = %f with P(x) = %f and %d iterations\n", root, froot, i);
        }
        else
        {
            printf("A root wasn't found. Finished with x = %f with P(x) = %f and %d iterations\n", root, froot, i);
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
    expected.set(0.3873, 0, 1);
    testPolynomial(p, -5, 5, expected, passedCount, failedCount);

    // P(x) = -100 + 2.25x
    p.set({-100, 2.25});
    expected.set(44.4444, 0, 1);
    testPolynomial(p, -5, 5, expected, passedCount, failedCount);

    printf("   ________________________________________________________________   ");
    printf("\n");
    printf("\n");
}

void testForConstantMonomialZero(int& passedCount, int& failedCount)
{

}

void testForMixedPolynomial(int& passedCount, int& failedCount)
{

}

void testForPolynomialsWithDecimals(int& passedCount, int& failedCount)
{

}

void testForBigPolynomials(int& passedCount, int& failedCount)
{

}

void testForHugePolynomials(int& passedCount, int& failedCount)
{

}

void testForNonRootPolynomials(int& passedCount, int& failedCount)
{

}

void testForFarInitialValues(int& passedCount, int& failedCount)
{

}

void runAllTests()
{
    int testsPassed = 0;
    int testsFailed = 0;

    testForConstantPolynomials(testsPassed, testsFailed);
    testForDegreeOnePolynomial(testsPassed, testsFailed);
    testForConstantMonomialZero(testsPassed, testsFailed);
    testForMixedPolynomial(testsPassed, testsFailed);
    testForPolynomialsWithDecimals(testsPassed, testsFailed);
    testForBigPolynomials(testsPassed, testsFailed);
    testForHugePolynomials(testsPassed, testsFailed);
    testForNonRootPolynomials(testsPassed, testsFailed);
    testForFarInitialValues(testsPassed, testsFailed);
    printf("\n");
    printf("%d Tests completed. Succeeded tests: %d, Failed tests: %d", testsPassed + testsFailed, testsPassed, testsFailed);
    printf("\n");
    printf("\n");
}
