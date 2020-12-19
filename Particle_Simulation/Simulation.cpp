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
    // the boundary condition parameters
    static const double Xmin = -10;
    static const double Xmax = 10;
    static const double Ymin = -10;
    static const double Ymax = 10;
    // end of boundary condition parameters

    // parameters of the particles
    static const double Angle_velocity_max = 0.5;
    static const int total_particle = 1000000;
    static const double vbar = 50;
    
    static const int Z = 15;
       int a = Z+1;
        double b = vbar / (Z + 1); //3.125;
    // end of parameters of the particles


    const double v = 3;
    const double c = 4;
    const double g = 5;

    // the parameter of the simulation
    static const double dt = 0.05; // the time of each step
    static const int total_time_step = 100000; //total step number of the simulation
    // end of parameters of simulation

    // random related staff
    std::mersenne_twister_engine<std::uint_fast64_t, 64, 312, 156, 31,
        0xb5026f5aa96619e9, 29,
        0x5555555555555555, 17,
        0x71d67fffeda60000, 37,
        0xfff7eee000000000, 43, 6364136223846793005> generator;
    std::gamma_distribution<double> gamma(a, b);
    std::uniform_real_distribution<double> Xdis(Xmin, Xmax);
    std::uniform_real_distribution<double> Ydis(Ymin, Ymax);
    std::uniform_real_distribution<double> Angledis(0, 2 * acos(-1));
    std::uniform_real_distribution<double> Angle_velocity_dis(-Angle_velocity_max, Angle_velocity_max);
    generator.seed(time(NULL));
    // end of random related staff

    
    static Particle M[total_particle];
    M[0].setParticle(Xdis(generator), Ydis(generator), Angledis(generator), gamma(generator), g);
    M[0].printPoint();
    cout << "The velocity is "<<M[0].get_Velocity() << endl;
    M[0].update(dt);
    M[0].printPoint();
    M[0].Boundary(Xmin, Xmax , Ymin , Ymax);
    M[0].printPoint();

    //progressbar bar(total_particle);
    for (int i = 0; i < total_particle; ++i) 
    {
        M[i].setParticle(Xdis(generator), Ydis(generator), Angledis(generator), gamma(generator), Angle_velocity_dis(generator));
        //bar.update();

        // ... the program
    }
    cout << "\n" << endl;
    M[12].printPoint();
    M[13].printPoint();


    return(0);


}