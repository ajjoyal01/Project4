#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "vmath.h"
//#include "vec.h"
using namespace std;

void loadObject(const char* filename, vector<vmath::vec4> &vertices, vector<vmath::vec3> &normals, vector<GLushort> &elements)
{
	ifstream in(filename, ios::in);

	if (!in)
	{
		cerr << "Cannot open " << filename << endl;
		exit(1);
	}

	string line;
	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			vmath::vec4 v;
			float x, y, z, w;
			s >> x;
			s >> y;
			s >> z;
			w = 1.0f;
			v = vmath::vec4(x, y, z, w);
			vertices.push_back(v);
		}
		else
		{
			if (line.substr(0, 2) == "f ")
			{
				istringstream s(line.substr(2));
				GLushort a, b, c;
				s >> a;
				s >> b;
				s >> c;
				a--;
				b--;
				c--;
				elements.push_back(a);
				elements.push_back(b);
				elements.push_back(c);
			}
			else
			{
				if (line.substr(0, 3) == "vn ")
				{
					istringstream s(line.substr(3));
					vmath::vec3 v;
					float x, y, z;
					s >> x;
					s >> y;
					s >> z;
					v = vmath::vec3(x, y, z);
					normals.push_back(v);
				}
			}
		}
	}
}