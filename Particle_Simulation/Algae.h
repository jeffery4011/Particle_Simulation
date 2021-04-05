#ifndef _Algae_H_
#define _Algae_H_

#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "D_eff.h"
using namespace std;

class Algae
{
public:
    void setAlgae(double x, double y, double angle, double linear_velocity, int running_time, int tumble_time=0);// set the position, angluar, linear velocity , running_time and tumble_time of the particle
    void printAlgae();// print the algae position x,y
    //void update(double x, double part1, double part2, double D_high, double D_low, double D_regular, int t, double light_cycle, double light_on, double Vbar, double dt); // update the particle according to its current linear_velocity and angular_velocity
    void update(double dt);
    void Boundary(double X_min, double X_max, double Y_min, double Y_max); // the boundary of algae, update its new position in bondary
    void velocity_set(double v);//stop the algae
    void tumble_set(int tumbletime);// set the new tumble time
    void running_set(int runningtime);//set new running time
    void angleset(double angle);//set the angle

    //get the value of the algae
    double get_X();
    double get_Y();
    double get_Velocity();
    double get_angle();
    int get_running_time();
    int get_tumble_time();
    //end of the value of the algae


private:
    double xPos;
    double yPos;
    double anglePos;
    double linear_velocity_set;
    int running_time_set;
    int tumble_time_set;
};

#endif#pragma once
