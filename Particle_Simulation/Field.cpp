#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Field.h"

using namespace std;

//the function of D_fun 
//F_high is the highest value of the field
//F_low is the lowest value of the field
// part1 is the increasing length part2 is decreasing length

double Field_fun_up(double x, double F_high, double F_low, double part1, double part2)
{
	return ((F_high - F_low) * x / part1 + F_low);
}
double Field_fun_down(double x, double F_high, double F_low, double part1, double part2)
{
	return ((F_low - F_high) * x / part2 - (part1 * F_low - (part1 + part2) * F_high) / part2);
}

// end of function of D_fun

// light determine
bool islight_on(double t, double light_cycle, double light_on)
{
	return ((t - floor(t / light_cycle) * light_cycle) < light_on);
}
// end of ligh determin 

// D_eff part determine if true, it's in part1
bool Field_part(double x, double part1, double part2)
{
	if (x >= 0)
		return (fmod(x, (part1 + part2)) < part1);
	else
		return(fmod(-x, (part1 + part2)) > part2);
}
// end of D_eff part determine

// Calculate the D_eff
double Field_value(double x, double part1, double part2, double F_high, double F_low, double F_regular, double t, double light_cycle, double light_on)
{
	if (!islight_on(t, light_cycle, light_on))
	{
		return F_regular;
	}
	else
	{
		if (x > 0)
		{
			x = fmod(x, (part1 + part2));
		}
		if (x < 0)
		{
			x = fmod(x, -(part1 + part2)) + (part1 + part2);
		}


		if (Field_part(x, part1, part2))
		{

			return Field_fun_up(x, F_high, F_low, part1, part2);
		}
		else
		{

			return Field_fun_down(x, F_high, F_low, part1, part2);
		}
	}

}
// end of calculation

double Field_derivative(double x, double part1, double part2, double F_high, double F_low, double F_regular, double t, double light_cycle, double light_on)
{
	if (!islight_on(t, light_cycle, light_on))
	{
		return 10;
	}
	else
	{
		if (x > 0)
		{
			x = fmod(x, (part1 + part2));
		}
		if (x < 0)
		{
			x = fmod(x, -(part1 + part2)) + (part1 + part2);
		}


		if (Field_part(x, part1, part2))
		{

			return (F_high - F_low) / part1;
		}
		else
		{

			return (F_low - F_high) / part2;
		}
	}
}
