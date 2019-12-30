# Example Project - Secant Method
[![License](https://img.shields.io/github/license/TobiasBriones/example.math.numerical.polynomial.cpp.secant_method)](https://github.com/TobiasBriones/example.math.numerical.polynomial.cpp.secant_method/blob/master/LICENSE)

Example project for computing the roots of the given polynomial through the secant method to get the approximations, written in a C++ console application.

### Notes
If you wish to extend this project just take into account some considerations:
* Clearing the console only worked for me when debugging with VS, not when running the generated executable
* Get aware of how to take the results, in this case, I computed the algorithm without rounding anything until finishing and then rounding the x value found and also rounding P(x) according to the decimal precision of 4 decimals
* The coefficient implementation for the polynomial class can be optimized to avoid storing huge polynomials with lots of zero coefficients, it was just not necessary to do for this project
* I didn't handle when a root was found but outside of [a, b], it's up to you
* The iterations can be printed, consider when the number of iterations is less than a small number to avoid polluting the console with hundreds of iterations

![screenshot_1](https://github.com/TobiasBriones/example.math.numerical.polynomial.cpp.secant_method/blob/master/_Repo/Assets/Screenshot_1.png)

![screenshot_2](https://github.com/TobiasBriones/example.math.numerical.polynomial.cpp.secant_method/blob/master/_Repo/Assets/Screenshot_2.png)
