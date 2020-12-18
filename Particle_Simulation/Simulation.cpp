#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Particle.h"
#include "progressbar.hpp"

using namespace std;

int main()
{
    const double a = 1;
    const double b = 2;
    const double v = 3;
    const double c = 4;
    const double g = 5;
    const double dt = 0.5;

    Particle M;
    double* e = (double*)&M;
    M.setParticle(a, b, v, c, g);
    M.printPoint();
    //cout << "The position of x is "<<M.get_X() << endl;
    M.update(dt);
    M.printPoint();
    M.Boundary(0, 2, 0, 2);
    M.printPoint();

    progressbar bar(10000);
    for (int i = 0; i < 10000; ++i) {
        bar.update();
        // ... the program
    }
    

    return(0);


}