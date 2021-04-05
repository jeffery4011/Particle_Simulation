#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <direct.h>
#include <fstream>
#include <string>
#include <thread>
#include "Algae.h"
#include "progressbar.hpp"
#include "D_eff.h"

using namespace std;

int main()
{
    // the boundary condition parameters
    static const double xmin = -50;
    static const double xmax = 50;
    static const double ymin = -10;
    static const double ymax = 10;
    // end of boundary condition parameters

    // field parameters
    static const double part1 = 1; // length of the up field 
    static const double part2 = 4; // length of down field
    static const double D_high = 0.03; // high value of the field when light on
    static const double D_low = 0.005; // low value of the field when light on
    static const double D_regular = 0.05; // regular value of the field when light off
    static const double light_cycle = 80000; //8e4 ligh cycle time
    static const double light_on = 40000; // 4e4 light on time
    // end of field parameters

    // parameters of the algae
    //static const double Angle_velocity_max = 0.5;
    static const int Total_particle = 10000;//1e5
    static const double Vbar = 50;// need to put in Algae.cpp


    static const int Z = 15;// need to put in Algae.cpp
    int A = Z + 1;// need to put in Algae.cpp
    double B = Vbar / (Z + 1); //3.125;// need to put in Algae.cpp
// end of parameters of the algae

    ofstream data_file;
    static int filenum = 0;
    
    static double X ;
    //const double c = 4;
    //const double g = 5;

    // the parameter of the simulation
    
    static const double dt = 0.02; // the time of each step
    static const int total_time_step = 80000; //total step number of the simulation 2e5
    // end of parameters of simulation

    // random related staff
    std::mersenne_twister_engine<std::uint_fast64_t, 64, 312, 156, 31,
        0xb5026f5aa96619e9, 29,
        0x5555555555555555, 17,
        0x71d67fffeda60000, 37,
        0xfff7eee000000000, 43, 6364136223846793005> generator;
    std::gamma_distribution<double> gamma(A, B);
    std::uniform_real_distribution<double> Xdis(-1, 1);
    std::uniform_real_distribution<double> Ydis(ymin, ymax);
    std::uniform_real_distribution<double> Tumbledis(0, 1);
    std::uniform_real_distribution<double> Angledis(0, 2 * acos(-1));
    //std::uniform_real_distribution<double> Angle_velocity_dis(-Angle_velocity_max, Angle_velocity_max);
    generator.seed(time(NULL));
    // end of random related staff


    static Algae M[Total_particle];
    fflush(stdin);
    _mkdir("Algae_Position");
    //ProgressBar bar(total_time_step);
    const char* path = "E:/±ÏÒµÂÛÎÄ/Flashing Ratchet/Simulation/Alagae_Simulation/Algae_Simulation/Algae_Simulation/Algae_Position/";
    const char* type = ".dat";
    int R_unning_time;

    // initialize
    for (int i = 0; i < Total_particle; ++i)
    {
        X = Xdis(generator);
        R_unning_time = running_time_D(X, part1, part2, D_high, D_low, D_regular, 0, light_cycle, light_on, Vbar, dt);
        M[i].setAlgae(X, Ydis(generator), Angledis(generator), 0.001*gamma(generator), R_unning_time, 0);
        
    }
    /*cout << "X is" << M[12].get_X() << endl;
    cout << "D_eff_value is" << D_eff_value(M[12].get_X(), part1,part2,D_high,D_low,D_regular,t,light_cycle,light_on) << endl;
    cout << "function running time is " << running_time_D(M[12].get_X(), part1, part2, D_high, D_low, D_regular, t, light_cycle, light_on, Vbar, dt) << endl;
    cout << "running time is" << M[12].get_running_time() << endl;
    cout << "running time is" << R_unning_time[12] << endl;*/
    //end of initialization


    for (int ii = 0; ii < total_time_step; ++ii)
    {
        //std::thread progress_thread(&ProgressBar::update, bar);
        if (ii % 100 == 0)  // each 100 step save file
        {
            std::string filename = path + std::to_string(filenum) + type;
            data_file.open(filename);
        }
        
        for (int i = 0; i < Total_particle; ++i)
        {
            
            if (M[i].get_running_time() > ii)
            {
                M[i].update(dt);
            }
            if (M[i].get_running_time() == ii)
            {
                M[i].velocity_set(0);
                M[i].tumble_set(round(Tumbledis(generator) / dt));
            }
            if (M[i].get_running_time() < ii)
            {
                if (M[i].get_tumble_time() == 0)
                {
                    M[i].running_set(ii + running_time_D(M[i].get_X(), part1, part2, D_high, D_low, D_regular, ii, light_cycle, light_on, Vbar, dt));
                    M[i].velocity_set(0.001 * gamma(generator));
                    M[i].angleset(Angledis(generator));
                }
                else
                {
                    M[i].velocity_set(0);
                    M[i].tumble_set(M[i].get_tumble_time()-1);
                }
            }

            //M[i].update( M[i].get_X(), part1, part2, D_high, D_low, D_regular, ii, light_cycle, light_on, Vbar, dt);
            M[i].Boundary(xmin, xmax, ymin, ymax);
            


            if (data_file.is_open())
            {
                data_file <<  M[i].get_X() << ";" << M[i].get_Y()  << '\n';
            }

        }
        //m[13].printalgae();
        if (data_file.is_open())
        {
            data_file.close();
            filenum = filenum + 1;
        }
        //progress_thread.join();
        //bar.update();
        //cout << "velocity is" <<M[12].get_Velocity() << endl;
        //cout << "running_time is" << M[12].get_running_time() << endl;
        //cout << "tumble time is" << M[12].get_tumble_time() << endl;
    }
    //bar.finish();
    //std::thread progress_thread(&ProgressBar::finish, bar);
    //progress_thread.join();

    return(0);


}