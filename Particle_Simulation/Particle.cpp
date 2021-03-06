#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Particle.h"

using namespace std;

// set the position, angluar, linear velocity and angular velocity of the particle
void Particle::setParticle(double x, double y, double angle, double linear_velocity, double angular_velocity)
{
    xPos = x;
    yPos = y;
    anglePos = angle;
    linear_velocity_set = linear_velocity;
    angular_velocity_set = angular_velocity;
}

// print the particle position x,y
void Particle::printPoint()
{
    cout << "x = " << xPos << endl;
    cout << "y = " << yPos << endl;
    cout << "angle = " << anglePos << endl;
}

// update the particle according to its current linear_velocity and angular_velocity
void Particle::update(double dt)
{
    xPos = xPos + linear_velocity_set * cos(anglePos) * dt;
    yPos = yPos + linear_velocity_set * sin(anglePos) * dt;
    anglePos = anglePos + angular_velocity_set * dt;
}

// the boundary of particle, update its new position in boundary
void Particle::Boundary(double X_min, double X_max, double Y_min, double Y_max)
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


void Particle::set_linear_velocity(double v)
{
    linear_velocity_set = v;
}

void Particle::set_angular_velocity(double w)
{
    angular_velocity_set = w;
}

//get the value of the particle
double Particle::get_X() { return xPos; }

double Particle::get_Y() { return yPos; }

double Particle::get_Velocity() { return linear_velocity_set; }

double Particle::get_angle() { return anglePos; }

double Particle::get_angle_velocity() { return angular_velocity_set; }

double Particle::get_derivative(double F_forward, double F_backward, double sensor_r, double sensor_diff)
{
    if (F_forward > F_backward + sensor_diff / 2) { return 1; }
    else {
        if (F_backward > F_forward + sensor_diff) { return -1; }
        else { return 1; }
    }
}
//end of the value of the particle