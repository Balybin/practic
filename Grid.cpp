#pragma once
#include "Grid.h"
#include "glut.h"
#include "Palitra.h"

extern bool LineFlag, isBiquaratic, additionalNodes;
extern double xPosition, yPosition, zPosition;
extern GLint Width, Height;
extern GLubyte ColorR, ColorG, ColorB;
extern GLubyte PointSize;
extern Palitra palitra;

int Grid::calculatePosistion(int i, int j)
{
	if (i >= X.size() || j >= Y.size() || i < 0 || j < 0)
		return -1;
	int k = j * X.size() + i;
	if (k >= 0)
		return k;
	else
		return -1;
}
void Grid::inputGrid(fstream in)
{
	if (!in.is_open())
	{
		std::cout << "can't open input file" << endl;
		system("pause");
		exit(1);
	}
	string flag;
	double buf;
	in >> flag; //(x:)
	while (1)
	{
		in >> flag;
		if (flag == "y:")
			break;
		buf = atof(flag.c_str());
		X.push_back(buf);
	}
	while (1)
	{
		in >> flag;
		if (flag == "U(x,y):")
			break;
		buf = atof(flag.c_str());
		Y.push_back(buf);
	}
	while (in >> buf)
	{
		U.push_back(buf);
	}
}

void Grid::displayBilinearGrid()
{
	int r, g, b;
	int n = X.size() - 1, m = Y.size() - 1;
	glClearColor(0.2, 0.2, 0.2, 1); glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(xPosition, yPosition, 0);
	glScaled(5000 * zPosition, 5000 * zPosition, 1);
	glColor3ub(ColorR, ColorG, ColorB);
	glPointSize(PointSize);
	glLineWidth(1);

	if (LineFlag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int j = 0; j < m; ++j)
	{
		for(int i=0; i < n; ++i)
		{
			glBegin(GL_QUADS);
			palitra.color(r, g, b, U[calculatePosistion(i, j)]);
			glVertex2f(X[i], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j)]);
			glVertex2f(X[i + 1], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i, j + 1)]);
			glVertex2f(X[i], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
			glVertex2f(X[i + 1], Y[j + 1]);
			glEnd();
		}
	}
	if (!LineFlag)
	{
		glColor3ub(0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (int j = 0; j < m; ++j)
		{
			for (int i = 0; i < n; ++i)
			{
				glBegin(GL_QUADS);
				palitra.color(r, g, b, U[calculatePosistion(i, j)]);
				palitra.color(r, g, b, U[calculatePosistion(i + 1, j)]);
				palitra.color(r, g, b, U[calculatePosistion(i, j + 1)]);
				palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
				glEnd();
			}
		}
	}
	glFinish();
}

void Grid::displayBiqudraticGrid()
{

}
