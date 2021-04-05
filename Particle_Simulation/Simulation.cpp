#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <direct.h>
#include <fstream>
#include <string>
#include <thread>
#include "Particle.h"
#include "Field.h"
#include "progressbar.hpp"

using namespace std;
static const int sensor_diff = 10;

double Linear_Field_relation(double Field_value, double V_max)
{
    double R = V_max / 100 * Field_value; //the V(I(x))
    return (R);
}

double Angular_Field_relation(int F_forward, int F_backward, double W_max, double noise, double noise_constant)
{
    //double R = W_max - W_max/ 255 * Field_value;//the D(I(x))_angular
    if (F_forward > F_backward + sensor_diff / 2 || F_backward > F_forward + sensor_diff) { return W_max + noise; }
    else { return noise_constant; }

}

int main()
{   
    // the boundary condition parameters
    static const double Xmin = -3600;//cm
    static const double Xmax = 3600; //cm
    static const double Ymin = -1200;//cm
    static const double Ymax = 1200;//cm
    // end of boundary condition parameters

    // parameters of the particles
    static const double sensor_r = 20;//cm
    static const double Angle_velocity_max = 0.2;
    static const int total_particle = 300000;
    static const double Linear_velocity_max = 15;// 2;//4;
    
    
    //static const int Z = 15;
      // int a = Z+1;
        //double b = vbar / (Z + 1); //3.125;
    // end of parameters of the particles


 

    // the parameter of the simulation
    
    static const double F_high = 900;//255;
    static const double F_low = 2;
    static const double F_regular = 5;//30;//60;//20;//105;
    static const double light_cycle = 450;//80000;
    static const double light_on = 200;//40000;
    static const double part1 = 45;//10;
    static const double part2 = 180;//40;
    static const double dt = 0.1; // the time of each step
    static const int total_time_step = 650;//40000;//100000; //total step number of the simulation
    static const double D_velociy = sqrt(2);
    static const double Angular_diff = 0.1;
    static const double Angular_const_diff = 2;
    static const double D_force = 2*Linear_velocity_max / (F_high - F_low) * part1;
    // end of parameters of simulation

    // random related staff
    std::mersenne_twister_engine<std::uint_fast64_t, 64, 312, 156, 31,
        0xb5026f5aa96619e9, 29,
        0x5555555555555555, 17,
        0x71d67fffeda60000, 37,
        0xfff7eee000000000, 43, 6364136223846793005> generator;
    std::uniform_real_distribution<double> Vdis(0, Linear_velocity_max/100);
    //std::uniform_real_distribution<double> Xdis(Xmin, Xmax);
    std::uniform_real_distribution<double> Xdis(-1, 1);
    std::uniform_real_distribution<double> Ydis(Ymin, Ymax);
    std::uniform_real_distribution<double> Angledis(0, 2 * acos(-1));
    std::uniform_real_distribution<double> Angle_velocity_dis(-Angle_velocity_max, Angle_velocity_max);
    //std::normal_distribution<double> Linear_noise(0, Linear_velocity_max / 10000);
    //std::normal_distribution<double> Linear_noise(0, Linear_velocity_max /30);
    //std::normal_distribution<double> Angular_noise(0, Angle_velocity_max / 1);
    std::normal_distribution<double> Angular_noise(0, Angular_diff);
    std::normal_distribution<double> Angular_const_noise(0, Angular_const_diff);
    generator.seed(time(NULL));
    // end of random related staff

    
    static Particle M[total_particle];
    fflush(stdin);
    _mkdir("E:/毕业论文/Flashing Ratchet/代码/Particle_Position");
    //ProgressBar bar(total_time_step);
    const char* path = "E:/毕业论文/Flashing Ratchet/代码/Particle_Position/";
    const char* type = ".dat";
    static int filenum = 0;
    ofstream data_file;

    //Initialization
    for (int i = 0; i < total_particle; ++i) 
    {
        M[i].setParticle(Xdis(generator), Ydis(generator), Angledis(generator),  Vdis(generator), Angle_velocity_dis(generator));          
    }
    //end of Initialization
    ProgressBar bar(total_time_step);
    for (int ii = 0; ii < total_time_step; ++ii)
    {
        if (ii % 10 == 0)  // each 10 step save file
        {
            std::string filename = path + std::to_string(filenum) + type;
            data_file.open(filename);
        }
        for (int i = 0; i < total_particle; ++i)
        {
            M[i].update(dt);
            M[i].Boundary(Xmin, Xmax, Ymin, Ymax);
            //double F = Field_value(M[i].get_X(), part1, part2, F_high, F_low, F_regular, ii, light_cycle, light_on);
            //double F_derivative = Field_derivative(M[i].get_X(), part1, part2, F_high, F_low, F_regular, ii, light_cycle, light_on);
            //M[i].set_linear_velocity(D_velociy *Linear_noise(generator)+Linear_Field_relation(F,Linear_velocity_max)); //update new velocity
            //M[i].set_angular_velocity(Angular_noise(generator) *sqrt(Angular_Field_relation(F, Angle_velocity_max))); // update new angular_velocity
            double F_for = Field_value(M[i].get_X()+sensor_r*cos(M[i].get_angle()), part1, part2, F_high, F_low, F_regular, ii, light_cycle, light_on);
            double F_back = Field_value(M[i].get_X()- sensor_r * cos(M[i].get_angle()), part1, part2, F_high, F_low, F_regular, ii, light_cycle, light_on);
            M[i].set_linear_velocity(-Linear_velocity_max * M[i].get_derivative(F_for, F_back, sensor_r,sensor_diff));
            double w_noise1 = Angular_noise(generator); double w_noise2 = Angular_const_noise(generator);
            M[i].set_angular_velocity(Angular_Field_relation(F_for,F_back, Angle_velocity_max,w_noise1,w_noise2));

            if (data_file.is_open())
            {
                data_file << M[i].get_X() << ";" << M[i].get_Y() << ";" << M[i].get_angle()<<";" << M[i].get_Velocity()<<";" << M[i].get_angle_velocity() << '\n';
            }
        }
        if (data_file.is_open())
        {
            data_file.close();
            filenum = filenum + 1;
        }
        


        bar.update();
    }
    
    bar.finish();


    return(0);


}