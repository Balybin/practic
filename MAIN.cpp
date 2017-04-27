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
bool isBiquaratic = false, additionalNodes;

Palitra palitra;
Grid grid;

GLint Width = 2*512, Height = 2*512;
GLubyte ColorR = 0, ColorG = 0, ColorB = 0;
GLubyte PointSize = 5;

enum keys { Empty, KeyR, KeyG, KeyB, KeyW, KeyA, KeyS, KeyD, KeyU,KeyI };

/* Функция вывода на экран */
void Display()
{
	if (isBiquaratic)
		grid.displayBiqudraticGrid();
	else
		grid.displayBilinearGrid();
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
	if (key == 'w' || key == 'ц') yPosition -= 10;
	if (key == 's' || key == 'ы') yPosition += 10;
	if (key == 'a' || key == 'ф') xPosition += 10;
	if (key == 'd' || key == 'в') xPosition -= 10;
	if (key == 32)
	{
		if (LineFlag)
			LineFlag = false;
		else
			LineFlag = true;
	}

	glutPostRedisplay();
}

/* Функция обработки сообщения от мыши */
//void Mouse(int button, int state, int x, int y)
//{
//	/* клавиша была нажата, но не отпущена */
//	if (state != GLUT_DOWN) return;
//
//	/* новая точка по левому клику */
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		type_point p(x, Height - y);
//		Points.push_back(p);
//	}
//	/* удаление последней точки по центральному клику */
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
//			glutAddMenuEntry("Компонента R", KeyR);
//			glutAddMenuEntry("Компонента G", KeyG);
//			glutAddMenuEntry("Компонента B", KeyB);
//
//			int menu_move = glutCreateMenu(Menu);
//			glutAddMenuEntry("Вверх",  KeyW);
//			glutAddMenuEntry("Вниз",   KeyS);
//			glutAddMenuEntry("Bлево",  KeyA);
//			glutAddMenuEntry("Вправо", KeyD);
//
//			int menu_size = glutCreateMenu(Menu);
//			glutAddMenuEntry("Увеличить", KeyU);
//			glutAddMenuEntry("Уменьшить", KeyI);
//
//			int menu = glutCreateMenu(Menu);
//			glutAddSubMenu("Смена цвета", menu_color);
//			glutAddSubMenu("Перемещение", menu_move);
//			glutAddSubMenu("Изменение размера точки", menu_size);
//
//			glutAttachMenu(GLUT_RIGHT_BUTTON);
//			Keyboard(Empty,0,0);
//	}
//}


/* Головная программа */
void main(int argc, char *argv[])
{
	ifstream in("F.txt");
	grid.inputGrid(in);
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
