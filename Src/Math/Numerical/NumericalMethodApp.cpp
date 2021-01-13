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

#include "NumericalMethodApp.h"

void NumericalMethodApp::clearScreen() const
{
    clear();
}

bool NumericalMethodApp::askToContinue(string msg) const
{
    printf("\n");
    printf("%s", msg.c_str());
    printf("\n");
    return _getch() == 13;
}

void NumericalMethodApp::showWelcome() const
{
    const string method = getName();

    printf(
        "                      ******************************************************************                      "
    );
    printf("\n");
    printf(
        "                    *                                                                    *                    "
    );
    printf("\n");
    printf(
        "                    *                          EXAMPLE PROJECT                           *                    "
    );
    printf("\n");
    printf(
        "                    *                                                                    *                    "
    );
    printf("\n");
    printf(
        "                    *  ________________________________________________________________  *                    "
    );
    printf("\n");
    printf(
        "                    *                                                                    *                    "
    );
    printf("\n");
    printf(
        "                    *                          NUMERICAL ANALYSIS                        *                    "
    );
    printf("\n");
    printf(
        "                    *                                                                    *                    "
    );
    printf("\n");
    printf("                    *");
    for (int i = 1; i < 70; i++)
    {
        if (i == 29)
        {
            string insert = method + " METHOD";

            printf("%s", insert.c_str());
            i += insert.length();
        }
        else
        {
            printf(" ");
        }
    }
    printf("*                    ");
    printf("\n");
    printf(
        "                    *                                                                    *                    "
    );
    printf("\n");
    printf(
        "                      ******************************************************************                      "
    );
    printf("\n");
    printf("\n");
}

bool NumericalMethodApp::showFooter() const
{
    printf("\n");
    printf("Great job by studying the Example Projects!");
    printf("\n");
    printf(
        "Learn more by accessing the Example Projects at https://tobiasbriones.engineer/ or https://github.com/TobiasBriones/"
    );
    printf("\n");
    printf("\n");
    return askToContinue("Press ENTER to continue, other key to exit");
}

int NumericalMethodApp::getInt(string msg) const
{
    int n;

    printf("%s", msg.c_str());
    cin >> n;

    if (!cin.good())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        throw runtime_error("Please enter an integer number");
    }
    return n;
}

double NumericalMethodApp::getDouble(string msg) const
{
    double n;

    printf("%s", msg.c_str());
    cin >> n;

    if (!cin.good())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        throw runtime_error("Please enter a real number");
    }
    return n;
}

void NumericalMethodApp::run()
{
    bool isRunning = true;

    do
    {
        reset();
        clearScreen();
        showWelcome();
        while (!gatherInput())
        {
            printf("\n");
            printf("\n");
        }
        if (!execute())
        {
            if (askToContinue("Press ENTER to restart, other key to exit"))
            {
                continue;
            }
            else
            {
                isRunning = showFooter();
                continue;
            }
        }
        showResults();
        isRunning = showFooter();
    }
    while (isRunning);
}
