#pragma once
#include "glut.h"
#include "Grid.h"

class Palitra
{
public:
	double red, blue, yellow, orange, green, minblue;
	void make(Grid grid)
	{
		double max, min;
		max = grid.U[0];
		min = grid.U[0];
		for (int i = 1; i < grid.U.size(); ++i)
		{
			if (grid.U[i] > max)	max = grid.U[i];
			if (grid.U[i] < min)	min = grid.U[i];
		}
		red = max;
		minblue = min;
		green = min + (max - min) / 2;
		yellow = max - (max - min) / 4;;
		blue = min + (max - min) / 4;;
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
				//z = (int)255 * (-value - (blue - minblue)) / (blue - minblue);
				z = 255 * (abs(blue - minblue) - abs(value - minblue)) / abs(blue - minblue);
				r = 0;	g = 255 - z; b = 255;
			}
			else
				if (value <= green-0.01)
				{
					//z = (int)255 * (-value - (green - yellow)) / (green - yellow);
					z = 255 * (abs(green - blue) - abs(value - blue)) / abs(green - blue);
					r = 0; g = 255; b = z;
				}
				else
					if (value <= yellow)
					{
						//z = (int)255 * (value - (yellow - green)) / (yellow - green);
						z = 255 * (abs(yellow - green) - abs(value - green)) / abs(yellow - green);
						r = 255 - z; g = 255; b = 0;
					}
					else
					{
						//z = (int)255 * (value - (red - yellow)) / (red - yellow);
						z = 255 * (abs(red - yellow) - abs(value - yellow)) / abs(red - yellow);
						r = 255; g = z; b = 0;
					}
	}
};