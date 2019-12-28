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

using std::string;
using std::cout;
using std::cin;
using std::endl;

/// <summary>
/// Defines an abstract class for creating a console app that solves numerical analysis problems.
/// </summary>
class NumericalMethodApp
{

private:
    void clearScreen() const;

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
    virtual void gatherInput() = 0;

    /// <summary>
    /// Executes the algorithm to produce the result of the numerical analysis.
    /// </summary>
    virtual void execute() = 0;

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

public:
    /// <summary>
    /// It is called when running a new numerical app on the console. The default implementation calls the standard
    /// processes defined in the base class, so if a different behaviour is needed it should be overriden by the
    /// respective subclass.
    /// </summary>
    void run();

};
