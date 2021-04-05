#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "D_eff.h"

using namespace std;

//the function of D_fun 
//D_high is the highest value of the field
//D_low is the lowest value of the field
// part1 is the increasing length part2 is decreasing length

double D_fun_up(double x, double D_high, double D_low, double part1, double part2)
{
	return ((D_high - D_low) * x / part1 + D_low);
}
double D_fun_down(double x, double D_high, double D_low, double part1, double part2)
{
	return ((D_low - D_high) * x / part2 - (part1 * D_low - (part1 + part2) * D_high) / part2);
}

// end of function of D_fun

// light determine
bool islight_on(double t, double light_cycle, double light_on)
{
	return ( (t - floor(t/light_cycle)*light_cycle)< light_on);
}
// end of ligh determin 

// D_eff part determine if true, it's in part1
bool D_part(double x, double part1, double part2)
{
	if (x >= 0)
		return (fmod(x, (part1 + part2 )) < part1);
	else
		return(fmod(-x, (part1 + part2 )) > part2);
}
// end of D_eff part determine

// Calculate the D_eff
double D_eff_value(double x, double part1, double part2, double D_high, double D_low, double D_regular, double t, double light_cycle, double light_on)
{
	if (islight_on(t, light_cycle, light_on))
		if (x > 0)
		{
			x = fmod(x, (part1 + part2));
		}
		if (x < 0)
		{
		x = fmod(x, -(part1 + part2)) + (part1 + part2);
		}
		

		if (D_part(x, part1, part2))
		{

			return D_fun_up(x, D_high, D_low, part1, part2);
		}
		else
		{

			return D_fun_down(x, D_high, D_low, part1, part2);
		}
	
	return D_regular;

}
// end of calculation

// Calculate the running_time
int running_time_D(double x, double part1, double part2, double D_high, double D_low, double D_regular, double t, double light_cycle, double light_on, double vbar, double dt)
{
	double Deff = D_eff_value(x, part1, part2, D_high, D_low, D_regular, t, light_cycle, light_on);
	return (round((2*Deff)/pow(vbar*0.001,2)/dt));

}
// end of calculation