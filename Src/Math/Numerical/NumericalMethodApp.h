/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdexcept>
#include "../../Console/Console.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;

/// <summary>
/// Defines an abstract class for creating a console app that solves numerical analysis problems.
/// </summary>
class NumericalMethodApp
{

private:
    void clearScreen() const;
    bool askToContinue(string) const;

protected:
    /// <summary>
    /// Returns the numerical analysis method's name.
    /// </summary>
    /// <returns>
    /// Returns the numerical analysis method's name
    /// </returns>
    virtual string getName() const = 0;

    /// <summary>
    /// Gets the basic input from the user required to execute the algorithm.
    /// </summary>
    /// <returns>
    /// Returns true if and only if the app obtained valid user input
    /// </returns>
    virtual bool gatherInput() = 0;

    /// <summary>
    /// Executes the algorithm to produce the result of the numerical analysis.
    /// </summary>
    /// <returns>
    /// Returns true if and only if the app successfully executed the computation
    /// </returns>
    virtual bool execute() = 0;

    /// <summary>
    /// Shows the results obtained from the program.
    /// </summary>
    virtual void showResults() const = 0;

    /// <summary>
    /// Clears the information of the algorithm.
    /// </summary>
    virtual void reset() = 0;

    /// <summary>
    /// Shows the welcome of the program.
    /// </summary>
    void showWelcome() const;

    /// <summary>
    /// Shows the end of the program.
    /// </summary>
    /// <returns>
    /// Returns true if and only if the app will continue executing for a new problem to compute
    /// </returns>
    bool showFooter() const;

    /// <summary>
    /// Asks an integer from the user input. It throws runtime error only if the user input is invalid.
    /// </summary>
    /// <returns>
    /// Returns the integer number the user entered
    /// </returns>
    int getInt(string msg) const;

    /// <summary>
    /// Asks a double from the user input. It throws runtime error only if the user input is invalid.
    /// </summary>
    /// <returns>
    /// Returns the double number the user entered
    /// </returns>
    double getDouble(string msg) const;

public:
    /// <summary>
    /// It is called when running a new numerical app on the console. The default implementation calls the standard
    /// processes defined in the base class, so if a different behaviour is needed it should be overriden by the
    /// respective subclass.
    /// </summary>
    void run();

};
