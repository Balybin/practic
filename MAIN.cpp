/*
Отключено консольное (главное) окно:
	Linker ->  Advanced -> Entery Point := "mainCRTStartup"
	Linker ->  System -> SubSystem := "Windows (/SUBSYSTEM:WINDOWS)"
*/

#include <stdlib.h>
#include "glut.h"
#include <vector>
#include "Grid.h"
#include <fstream>
#include <iostream>
#include "Palitra.h"
#include "Lines.h"

using namespace std;

double xPosition = 0, yPosition = 0, zPosition = 1;

bool LineFlag = false;
bool isBiquaratic = true, additionalNodes;
bool palitraFlag = false;
bool osiFlag = true;

std::ifstream in;

Palitra palitra;
Grid grid;

GLint Width = 2*512, Height = 2*512;
GLubyte ColorR = 0, ColorG = 0, ColorB = 0;
GLubyte PointSize = 2;

enum keys { Empty, KeyR, KeyG, KeyB, KeyW, KeyA, KeyS, KeyD, KeyU,KeyI };

void renderBitmapString(
	float x,
	float y,
	void *font,
	string str) {
	glRasterPos2f(x, y);
	const char *c = str.c_str();
	for (int i = 0; c[i] != '\0'; ++i)
	{
		glutBitmapCharacter(font, c[i]);
	}
	/*for (c = str.c_str; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}*/
}

/* Функция вывода на экран */
void Display()
{
	glClearColor(0.2, 0.2, 0.2, 1); glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(PointSize);
	glLineWidth(1);
	if (palitraFlag)
	{
		glTranslatef(1, 250, 1);
		glScaled(5, 5, 1);
		int r, g, b;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		palitra.color(r, g, b, palitra.minblue);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex2i(-50,50);
		glVertex2i(-50, 0);
		palitra.color(r, g, b, palitra.blue);
		glColor3ub(r, g, b);
		glVertex2i(-25, 0);
		glVertex2i(-25, 50);
		glVertex2i(-25, 0);
		glVertex2i(-25, 50);
		palitra.color(r, g, b, palitra.green);
		glColor3ub(r, g, b);
		glVertex2i(0, 50);
		glVertex2i(0, 0);
		glVertex2i(0, 50);
		glVertex2i(0, 0);
		palitra.color(r, g, b, palitra.yellow);
		glColor3ub(r, g, b);
		glVertex2i(25, 0);
		glVertex2i(25, 50);
		glVertex2i(25, 0);
		glVertex2i(25, 50);
		palitra.color(r, g, b, palitra.red);
		glColor3ub(r, g, b);
		glVertex2i(50, 50);
		glVertex2i(50, 0);
		glEnd();
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x00F0);
		glBegin(GL_LINES);
		glColor3ub(0, 0, 0);
		glVertex2i(-50, 50);
		glVertex2i(-50, 0);
		glVertex2i(-25, 0);
		glVertex2i(-25, 50);
		glVertex2i(0, 50);
		glVertex2i(0, 0);
		glVertex2i(25, 0);
		glVertex2i(25, 50);
		glVertex2i(50, 50);
		glVertex2i(50, 0);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glColor3ub(255, 255, 255);
		renderBitmapString(-50, 50, GLUT_BITMAP_HELVETICA_12, palitra.Minblue);
		renderBitmapString(-25, 50, GLUT_BITMAP_HELVETICA_12, palitra.Blue);
		renderBitmapString(0, 50, GLUT_BITMAP_HELVETICA_12, palitra.Green);
		renderBitmapString(25, 50, GLUT_BITMAP_HELVETICA_12, palitra.Yellow);
		renderBitmapString(50, 50, GLUT_BITMAP_HELVETICA_12, palitra.Red);
	}
	else
	{
		glTranslatef(xPosition, yPosition, 0);
		glScaled(500 * zPosition, 500 * zPosition, 1);
		if (isBiquaratic)
			grid.displayBiqudraticGrid();
		else
			grid.displayBilinearGrid();
		if (osiFlag)
		{
			glLineWidth(2);
			glBegin(GL_LINES);
			glColor3ub(0, 0, 0);
			glVertex2f(grid.X[0], grid.Y[0]);
			glVertex2f(grid.X[grid.X.size() - 1] + 2, grid.Y[0]);
			glVertex2f(grid.X[0], grid.Y[0]);
			glVertex2f(grid.X[0], grid.Y[grid.Y.size() - 1] + 2);
			glEnd();
		}
		glRasterPos2f(grid.X[grid.X.size() - 1] + 0.1, grid.Y[0]);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
		glRasterPos2f(grid.X[0], grid.Y[grid.Y.size() - 1] + 0.1);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
	}
	glFinish();
}

/* Функция изменения размеров окна */
void Reshape(GLint w, GLint h)
{
	Width = w;    Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w/2, w/2, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Функция обработки сообщений от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'r' || key == 'к') zPosition += 0.1;
	if (key == 'f' || key == 'а') zPosition -= 0.1;
	if (key == 'w' || key == 'ц') yPosition -= 100 * -zPosition;
	if (key == 's' || key == 'ы') yPosition += 100 * -zPosition;
	if (key == 'a' || key == 'ф') xPosition += 100 * -zPosition;
	if (key == 'd' || key == 'в') xPosition -= 100 * -zPosition;
	if (key == 32)
	{
		if (LineFlag)
			LineFlag = false;
		else
			LineFlag = true;
	}
	if (key == 'z' || key == 'я')
	{
		if (additionalNodes)
			additionalNodes = false;
		else
			additionalNodes = true;
	}
	if (key == 'p' || key == 'з')
	{
		if (palitraFlag)
			palitraFlag = false;
		else
			palitraFlag = true;
	}
	if (key == 'o' || key == 'щ')
	{
		if (osiFlag)
			osiFlag = false;
		else
			osiFlag = true;
	}
	if (key == 'b' || key == 'и')
	{
		if (isBiquaratic)
		{
			isBiquaratic = false;
			in.open("bilin.txt");
			grid.U.clear();
			grid.X.clear();
			grid.Y.clear();
			grid.inputGrid(in);
		}
		else
		{
			in.open("biquad.txt");
			grid.U.clear();
			grid.X.clear();
			grid.Y.clear();
			grid.inputGrid(in);
			isBiquaratic = true;
		}
	}
	glutPostRedisplay();
}

/* Головная программа */
void main(int argc, char *argv[])
{
	in.open("biquad.txt");
	grid.inputGrid(in);
	in.close();
	palitra.make(grid);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Результат");
	//Menu(Empty);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	//glutMouseFunc(Mouse);

	glutMainLoop();
}
