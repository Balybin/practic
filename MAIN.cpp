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
bool isBiquaratic = false, additionalNodes;

Palitra palitra;
Grid grid;

GLint Width = 2*512, Height = 2*512;
GLubyte ColorR = 0, ColorG = 0, ColorB = 0;
GLubyte PointSize = 5;

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
	if (key == 'w' || key == '�') yPosition -= 10;
	if (key == 's' || key == '�') yPosition += 10;
	if (key == 'a' || key == '�') xPosition += 10;
	if (key == 'd' || key == '�') xPosition -= 10;
	if (key == 32)
	{
		if (LineFlag)
			LineFlag = false;
		else
			LineFlag = true;
	}

	glutPostRedisplay();
}

/* ������� ��������� ��������� �� ���� */
//void Mouse(int button, int state, int x, int y)
//{
//	/* ������� ���� ������, �� �� �������� */
//	if (state != GLUT_DOWN) return;
//
//	/* ����� ����� �� ������ ����� */
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		type_point p(x, Height - y);
//		Points.push_back(p);
//	}
//	/* �������� ��������� ����� �� ������������ ����� */
//	if (button == GLUT_MIDDLE_BUTTON)
//	{
//		Points.pop_back();
//	}
//
//	glutPostRedisplay();
//}
//
//void Menu(int pos)
//{
//	int key = (keys)pos;
//
//	switch (key)
//	{
//		case KeyR: Keyboard('r', 0, 0); break;
//		case KeyG: Keyboard('g', 0, 0); break;
//		case KeyB: Keyboard('b', 0, 0); break;
//		case KeyW: Keyboard('w', 0, 0); break;
//		case KeyS: Keyboard('s', 0, 0); break;
//		case KeyA: Keyboard('a', 0, 0); break;
//		case KeyD: Keyboard('d', 0, 0); break;
//		case KeyU: Keyboard('u', 0, 0); break;
//		case KeyI: Keyboard('i', 0, 0); break;
//
//		default:
//			int menu_color = glutCreateMenu(Menu);
//			glutAddMenuEntry("���������� R", KeyR);
//			glutAddMenuEntry("���������� G", KeyG);
//			glutAddMenuEntry("���������� B", KeyB);
//
//			int menu_move = glutCreateMenu(Menu);
//			glutAddMenuEntry("�����",  KeyW);
//			glutAddMenuEntry("����",   KeyS);
//			glutAddMenuEntry("B����",  KeyA);
//			glutAddMenuEntry("������", KeyD);
//
//			int menu_size = glutCreateMenu(Menu);
//			glutAddMenuEntry("���������", KeyU);
//			glutAddMenuEntry("���������", KeyI);
//
//			int menu = glutCreateMenu(Menu);
//			glutAddSubMenu("����� �����", menu_color);
//			glutAddSubMenu("�����������", menu_move);
//			glutAddSubMenu("��������� ������� �����", menu_size);
//
//			glutAttachMenu(GLUT_RIGHT_BUTTON);
//			Keyboard(Empty,0,0);
//	}
//}


/* �������� ��������� */
void main(int argc, char *argv[])
{
	ifstream in("F.txt");
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
