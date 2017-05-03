#pragma once
#include "Grid.h"
#include "glut.h"
#include "Palitra.h"

extern bool LineFlag, isBiquaratic, additionalNodes,osiFlag;
extern double xPosition, yPosition, zPosition;
extern GLint Width, Height;
extern GLubyte ColorR, ColorG, ColorB;
extern GLubyte PointSize;
extern Palitra palitra;
extern void renderBitmapString(float x, float y, void *font, string str);

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
void Grid::inputGrid(ifstream &in)
{
	if (!in.is_open())
	{
		std::cout << "can't open input file" << endl;
		getchar();
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
	if (LineFlag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int j = 0; j < m; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			glBegin(GL_QUADS);
			palitra.color(r, g, b, U[calculatePosistion(i, j)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i], Y[j + 1]);
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
				palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
				palitra.color(r, g, b, U[calculatePosistion(i, j + 1)]);
				glEnd();
			}
		}
	}
	glColor3ub(0, 0, 0);
	if (osiFlag)
	{
		for (int i = 0; i < X.size(); i ++)
		{
			renderBitmapString(X[i], Y[0] - 0.1, GLUT_BITMAP_HELVETICA_10, to_string(X[i]));
		}

		for (int i = 0; i < Y.size(); i ++)
		{
			renderBitmapString(X[0] - 0.5, Y[i], GLUT_BITMAP_HELVETICA_10, to_string(X[i]));
		}
	}

}

void Grid::displayBiqudraticGrid()
{
	int r, g, b;
	int n = X.size() - 2, m = Y.size() - 2;
	if (LineFlag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int j = 0; j < m; j+=2)
	{
		for (int i = 0; i < n; i+=2)
		{
			glBegin(GL_QUADS);
			palitra.color(r, g, b, U[calculatePosistion(i, j)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 2, j)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 2], Y[j]);
			palitra.color(r, g, b, U[calculatePosistion(i + 2, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 2], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 2)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 2]);
			palitra.color(r, g, b, U[calculatePosistion(i, j + 2)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i], Y[j + 2]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 2, j + 1)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 2], Y[j + 1]);
			palitra.color(r, g, b, U[calculatePosistion(i + 2, j + 2)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 2], Y[j + 2]);
			palitra.color(r, g, b, U[calculatePosistion(i + 1, j + 2)]);
			glColor3ub(r, g, b);
			glVertex2f(X[i + 1], Y[j + 2]);
			glEnd();
		}
	}
	glColor3ub(0, 0, 0);
	if (osiFlag)
	{
		for (int i = 0; i < X.size(); i += 2)
		{
			renderBitmapString(X[i], Y[0] - 0.1, GLUT_BITMAP_HELVETICA_10, to_string(X[i]));
		}

		for (int i = 0; i < Y.size(); i += 2)
		{
			renderBitmapString(X[0] - 0.5, Y[i], GLUT_BITMAP_HELVETICA_10, to_string(X[i]));
		}
	}
	if (!LineFlag)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3ub(255, 255, 255);
		for (int j = 0; j < m; j += 2)
		{
			for (int i = 0; i < n; i += 2)
			{
				glBegin(GL_QUADS);
				glVertex2f(X[i], Y[j]);
				glVertex2f(X[i + 2], Y[j]);
				glVertex2f(X[i + 2], Y[j + 2]);
				glVertex2f(X[i], Y[j + 2]);
				glEnd();
			}
		}
		if (additionalNodes)
		{
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(1, 0x00F0);
			for (int j = 0; j < m; j += 2)
			{
				for (int i = 0; i < n; i += 2)
				{
					glColor3ub(255, 255, 255);
					glBegin(GL_LINES);
					glVertex2f(X[i + 1], Y[j]);
					glVertex2f(X[i + 1], Y[j + 2]);
					glVertex2f(X[i], Y[j + 1]);
					glVertex2f(X[i + 2], Y[j + 1]);
					glEnd();
					glColor3ub(0, 0, 0);
					glBegin(GL_POINTS);
					glVertex2f(X[i], Y[j]);
					glVertex2f(X[i], Y[j + 1]);
					glVertex2f(X[i], Y[j + 2]);
					glVertex2f(X[i + 1], Y[j]);
					glVertex2f(X[i + 1], Y[j + 1]);
					glVertex2f(X[i + 1], Y[j + 2]);
					glVertex2f(X[i + 2], Y[j]);
					glVertex2f(X[i + 2], Y[j + 1]);
					glVertex2f(X[i + 2], Y[j + 2]);
					glEnd();

				}
			}
			glDisable(GL_LINE_STIPPLE);
		}
	}
}
