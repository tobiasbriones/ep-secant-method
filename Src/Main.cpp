/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Math/Numerical/SecantMethodApp.h"

int main()
{
    SecantMethodApp app;
    
    Polynomial p(4);

    p.setCoefficient(0, 1);
    p.setCoefficient(1, 0);
    p.setCoefficient(2, 2);
    p.setCoefficient(3, 1);
    p.setCoefficient(4, 4);
    cout << p.eval(0);
    
    app.run();
	return 0;
}
