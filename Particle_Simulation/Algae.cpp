#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Algae.h"
#include "D_eff.h"

using namespace std;

// random staff from main 
static const int Vbar = 50;


static const int Z = 15;
int A = Z + 1;
double B = Vbar / (Z + 1); //3.125;

std::mersenne_twister_engine<std::uint_fast64_t, 64, 312, 156, 31,
    0xb5026f5aa96619e9, 29,
    0x5555555555555555, 17,
    0x71d67fffeda60000, 37,
    0xfff7eee000000000, 43, 6364136223846793005> generator;
std::gamma_distribution<double> gamma(A, B);
std::uniform_real_distribution<double> Tumbledis(0, 1);
std::uniform_real_distribution<double> Angledis(0, 2 * acos(-1));



// end of random staff

// set the position, angluar, linear velocity and angular velocity of the algae
void Algae::setAlgae(double x, double y, double angle, double linear_velocity, int running_time, int tumble_time)
{
    xPos = x;
    yPos = y;
    anglePos = angle;
    linear_velocity_set = linear_velocity;
    running_time_set = running_time;
    tumble_time_set = tumble_time;
}

// print the particle position x,y
void Algae::printAlgae()
{
    cout << "x = " << xPos << endl;
    cout << "y = " << yPos << endl;
}

// update the particle according to its current linear_velocity and angular_velocity
//void Algae::update(double x, double part1, double part2, double D_high, double D_low, double D_regular, int t, double light_cycle, double light_on, double Vbar, double dt)
void Algae::update(double dt)
{

    //if (running_time_set > t)
    {
        xPos = xPos + linear_velocity_set * cos(anglePos) * dt;
        yPos = yPos + linear_velocity_set * sin(anglePos) * dt;

    }
}
    
    
   
//    if (running_time_set == t)
//    {   
//        generator.seed(time(NULL));
//        linear_velocity_set = 0;
//        tumble_time_set = round(Tumbledis(generator)/dt);
//    }
//    if (running_time_set < t)
//        if (tumble_time_set == 0) //tumble_time finish
//        {   
//            generator.seed(time(NULL));
//            running_time_set = t+running_time_D(x, part1, part2, D_high, D_low, D_regular, t, light_cycle, light_on, Vbar, dt);
//            linear_velocity_set = 0.001 * gamma(generator);
//            anglePos = Angledis(generator);
//        }
//        else
//        {//tumble_time pass
//            linear_velocity_set = 0;
//            tumble_time_set = tumble_time_set - 1;
//        }
//        
//}

// the boundary of particle, update its new position in boundary
void Algae::Boundary(double X_min, double X_max, double Y_min, double Y_max)
{
    if (xPos > X_max)
    {
        xPos = X_min + xPos - X_max;
    }
    else
    {
        if (xPos < X_min)
        {
            xPos = X_max - (X_min - xPos);
        }
    }
    if (yPos > Y_max)
    {
        yPos = Y_min + yPos - Y_max;
    }
    else
    {
        if (yPos < Y_min)
        {
            yPos = Y_max - (Y_min - yPos);
        }
    }
}

void Algae::velocity_set(double velocity) { linear_velocity_set = velocity; }
void Algae::tumble_set(int tumbletime) { tumble_time_set = tumbletime; }
void Algae::running_set(int runningtime) { running_time_set = runningtime; }
void Algae::angleset(double angle) { anglePos = angle; }

//get the value of the particle
double Algae::get_X() { return xPos; }

double Algae::get_Y() { return yPos; }

double Algae::get_Velocity() { return linear_velocity_set; }

double Algae::get_angle() { return anglePos; }

int Algae::get_running_time() { return running_time_set; }

int Algae::get_tumble_time() { return tumble_time_set; }
//end of the value of the particle