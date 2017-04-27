#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "glut.h"
using namespace std;

struct duoble_point
{
	double x, y;
};

class Lines
{
public:
	vector< pair<duoble_point, duoble_point> > lines;
	pair<duoble_point, duoble_point> buf;
	void inputLines()
	{
		ifstream in("lines.txt");
		if (!in.is_open())
		{
			cout << "cant open file 'lines.txt'" << endl;
			system("pause");
			exit(1);
		}
		while (!in.eof())
		{
			in >> buf.first.x;
			in >> buf.first.y;
			in >> buf.second.x;
			in >> buf.second.y;
			lines.push_back(buf);
		}
		if (lines.size() == 0)
		{
			cout << "input lines : 0, hmmm, ist suspiciously" << endl;
			system("pause");
		}
	}
	void Drow()
	{
		glLineWidth(3);
		glBegin(GL_LINES);
		for (int k = 0; k < lines.size(); ++k)
		{
			glVertex2f(lines[k].first.x, lines[k].first.y);
			glVertex2f(lines[k].second.x, lines[k].second.y);
		}

	}
};