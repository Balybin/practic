#pragma once
#include "glut.h"
#include "Grid.h"

class Palitra
{
public:
	double red, blue, yellow, orange, green, minblue;
	void make(double max)
	{
		red = max;
		minblue = -max;
		green = 0;
		yellow = max / 2;
		blue = -yellow;
	}

	void color(int &r, int &g, int &b, double value)
	{
		int z;
		if (value <= minblue)
		{
			r = 0;	g = 0;	b = 255;
			return;
		}
		else
			if (value <= blue)
			{
				z = (int)255 * (-value - (blue - minblue)) / (blue - minblue);
				r = 0;	g = 255 - z; b = 255;
			}
			else
				if (value <= green-0.01)
				{
					z = (int)255 * (-value - (green - yellow)) / (green - yellow);
					r = 0; g = 255; b = 255 - z;
				}
				else
					if (value <= yellow)
					{
						z = (int)255 * (value - (yellow - green)) / (yellow - green);
						r = z; g = 255; b = 0;
					}
					else
					{
						z = (int)255 * (value - (red - yellow)) / (red - yellow);
						r = 255; g = 255 - z; b = 0;
					}
	}
};