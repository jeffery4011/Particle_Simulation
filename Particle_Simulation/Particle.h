#ifndef _Particle_H_
#define _Particle_H_

#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

class Particle
{
public:
    void setParticle(double x, double y, double angle, double linear_velocity, double angular_velocity);// set the position, angluar, linear velocity and angular velocity of the particle
    void printPoint();// print the particle position x,y
    void update(double dt); // update the particle according to its current linear_velocity and angular_velocity
    void Boundary(double X_min, double X_max, double Y_min, double Y_max); // the boundary of particle, update its new position in bondary
    
    //get the value of the particle
    double get_X();
    double get_Y();
    double get_Velocity();
    double get_angle();
    double get_angle_velocity();
    //end of the value of the particle


private:
    double xPos;
    double yPos;
    double anglePos;
    double linear_velocity_set;
    double angular_velocity_set;
};

#endif#pragma once
