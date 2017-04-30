#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

#include "point.hpp"
#include "nvtr.hpp"
#include "material.hpp"

using namespace std;
class Grid
{
public:
	vector <double> X,Y;
	vector <double> U;
	
	void Grid::displayBilinearGrid();
	void Grid::displayBiqudraticGrid();
	int calculatePosistion(int i, int j);
	void inputGrid(ifstream &in);
};