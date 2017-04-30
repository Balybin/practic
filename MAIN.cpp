/*
��������� ���������� (�������) ����:
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

Palitra palitra;
Grid grid;

GLint Width = 2*512, Height = 2*512;
GLubyte ColorR = 0, ColorG = 0, ColorB = 0;
GLubyte PointSize = 2;

enum keys { Empty, KeyR, KeyG, KeyB, KeyW, KeyA, KeyS, KeyD, KeyU,KeyI };

/* ������� ������ �� ����� */
void Display()
{

	if (isBiquaratic)
		grid.displayBiqudraticGrid();
	else
		grid.displayBilinearGrid();
}

/* ������� ��������� �������� ���� */
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

/* ������� ��������� ��������� �� ���������� */
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'r' || key == '�') zPosition += 0.1;
	if (key == 'f' || key == '�') zPosition -= 0.1;
	if (key == 'w' || key == '�') yPosition -= 100 * -zPosition;
	if (key == 's' || key == '�') yPosition += 100 * -zPosition;
	if (key == 'a' || key == '�') xPosition += 100 * -zPosition;
	if (key == 'd' || key == '�') xPosition -= 100 * -zPosition;
	if (key == 32)
	{
		if (LineFlag)
			LineFlag = false;
		else
			LineFlag = true;
	}
	if (key == 'z' || key == '�')
	{
		if (additionalNodes)
			additionalNodes = false;
		else
			additionalNodes = true;
	}
	glutPostRedisplay();
}

/* �������� ��������� */
void main(int argc, char *argv[])
{
	std::ifstream in("result.txt");
	grid.inputGrid(in);
	palitra.make(grid);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("���������");
	//Menu(Empty);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	//glutMouseFunc(Mouse);

	glutMainLoop();
}
