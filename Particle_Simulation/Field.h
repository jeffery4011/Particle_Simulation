#ifndef _D_eff_H_
#define _D_eff_H_

#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

//the function of D_fun 
//D_high is the highest value of the field
//D_low is the lowest value of the field
// part1 is the increasing length part2 is decreasing length

double Field_fun_up(double x, double F_high, double F_low, double part1, double part2);
double Field_fun_down(double x, double F_high, double F_low, double part1, double part2);

// end of function of D_fun

// light determine if return true ,then light is on
bool islight_on(double t, double light_cycle, double light_on);
// end of ligh determin 

// D_eff part determine
bool Field_part(double x, double part1, double part2);
// end of D_eff part determine

// Calculate the D_eff
double Field_value(double x, double part1, double part2, double F_high, double F_low, double F_regular, double t, double light_cycle, double light_on);
// end of calculation

double Field_derivative(double x, double part1, double part2, double F_high, double F_low, double F_regular, double t, double light_cycle, double light_on);


#endif#pragma once

