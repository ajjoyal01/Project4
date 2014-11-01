#include "Object.h"


Object::Object()
{
	
}


Object::~Object()
{
}

void Object::draw()
{
	glBindVertexArray(VAOs[0]);

	glEnableVertexAttribArray(vPosition);
	if (texels.size() > 0)
	{ 
		glEnableVertexAttribArray(vTexel);
	}
	if (normals.size() > 0)
	{ 
		glEnableVertexAttribArray(vNormal);
	}
	
	glVertexAttribI1i(vIsTransformed, isTransformed);

	glVertexAttrib4fv(vModelMatrix, &transform[0][0]);
	glVertexAttrib4fv(vModelMatrix + 1, &transform[1][0]);
	glVertexAttrib4fv(vModelMatrix + 2, &transform[2][0]);
	glVertexAttrib4fv(vModelMatrix + 3, &transform[3][0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Object::init(string filename)
{
	loadObject(filename);
	
	/*
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << vertices[i][j] << "\t";
		}
		cout << endl;
		if (texels.size() > 0)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << texels[i][j] << "\t";
			}
			cout << endl;
		}
		if (normals.size() > 0)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << normals[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}

	cout << vertices.size() << endl;
	*/

	// create Vertex Array
	glGenVertexArrays(1, VAOs);
	glBindVertexArray(VAOs[0]);

	// create Buffers
	glGenBuffers(4, Buffers);
	
	glEnableVertexAttribArray(vPosition);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vmath::vec4), &vertices[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(
		vPosition,			// attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);

	if (texels.size() > 0)
	{
		glEnableVertexAttribArray(vTexel);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, texels.size() * sizeof(vmath::vec2), &texels[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(
			vTexel, // attribute
			2,                  // number of elements per vertex, here (x,y,z)
			GL_FLOAT,           // the type of each element
			GL_FALSE,           // take our values as-is
			0,                  // no extra data between each position
			0                   // offset of first element
			);
	}

	if (normals.size() > 0)
	{
		glEnableVertexAttribArray(vNormal);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vmath::vec3), &normals[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(
			vNormal, // attribute
			3,                  // number of elements per vertex, here (x,y,z)
			GL_FLOAT,           // the type of each element
			GL_FALSE,           // take our values as-is
			0,                  // no extra data between each position
			0                   // offset of first element
			);
	}

	transform = vmath::mat4::identity();
	center = vec4(0.0, 0.0, 0.0, 1.0);

	isTransformed = 1;
}

// Gets vertex, texel, normal data
void Object::loadObject(string filename)
{
	vector<vmath::vec4> in_vertices;
	vector<vmath::vec3> in_normals;
	vector<vmath::vec2> in_texels;

	bool isTexel = false;
	bool isNormal = false;

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
			in_vertices.push_back(v);
		}
		else
		{
			if (line.substr(0, 3) == "vt ")
			{
				isTexel = true;
				istringstream s(line.substr(3));
				vmath::vec2 v;
				float x, y;
				s >> x;
				s >> y;
				v = vmath::vec2(x, y);
				in_texels.push_back(v);
			}
			else
			{
				if (line.substr(0, 3) == "vn ")
				{
					isNormal = true;
					istringstream s(line.substr(3));
					vmath::vec3 v;
					float x, y, z;
					s >> x;
					s >> y;
					s >> z;
					v = vmath::vec3(x, y, z);
					in_normals.push_back(v);
				}
				else
				{
					if (line.substr(0, 2) == "f ")
					{
						istringstream s(line.substr(2));
						
						if (!isNormal && !isTexel)
						{
							GLushort av, bv, cv;
							s >> av;
							s >> bv;
							s >> cv;
							vertices.push_back(in_vertices[--av]);
							vertices.push_back(in_vertices[--bv]);
							vertices.push_back(in_vertices[--cv]);
						}
						else if (!isTexel)
						{
							GLushort av, an, bv, bn, cv, cn;
							s >> av;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> an;
							s >> bv;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> bn;
							s >> cv;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> cn;
							vertices.push_back(in_vertices[--av]);
							vertices.push_back(in_vertices[--bv]);
							vertices.push_back(in_vertices[--cv]);
							normals.push_back(in_normals[--an]);
							normals.push_back(in_normals[--bn]);
							normals.push_back(in_normals[--cn]);
						}
						else if (!isNormal)
						{
							GLushort av, at, bv, bt, cv, ct;
							s >> av;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> at;
							s >> bv;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> bt;
							s >> cv;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> ct;
							vertices.push_back(in_vertices[--av]);
							vertices.push_back(in_vertices[--bv]);
							vertices.push_back(in_vertices[--cv]);
							texels.push_back(in_texels[--at]);
							texels.push_back(in_texels[--bt]);
							texels.push_back(in_texels[--ct]);
						}
						else if (isNormal && isTexel)
						{
							GLushort av, at, an, bv, bt, bn, cv, ct, cn;
							s >> av;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> at;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> an;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> bv;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> bt;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> bn;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> cv;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> ct;
							while (s.peek() == '/')
							{
								s.get();
							}
							s >> cn;
							while (s.peek() == '/')
							{
								s.get();
							}
							vertices.push_back(in_vertices[--av]);
							vertices.push_back(in_vertices[--bv]);
							vertices.push_back(in_vertices[--cv]);
							texels.push_back(in_texels[--at]);
							texels.push_back(in_texels[--bt]);
							texels.push_back(in_texels[--ct]);
							normals.push_back(in_normals[--an]);
							normals.push_back(in_normals[--bn]);
							normals.push_back(in_normals[--cn]);
						}
					}
				}
			}
		}
	}
}

void Object::scale(float scaleFactor)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 scale = vmath::scale(scaleFactor);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	transform = (translate2 * scale * translate1) * transform;
	updateCenter();
}

void Object::translate(float x, float y, float z)
{
	vmath::mat4 translate = vmath::translate(x, y, z);
	transform = translate * transform;
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << transform[j][i] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	*/
	updateCenter();
}

void Object::rotate(float angle, vmath::vec3 inAxis)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 rotate = vmath::rotate(angle, inAxis);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	transform = (translate2 * rotate * translate1) * transform;
	updateCenter();
}

void Object::deselect(Shader shader)
{
	//selected = false;

	//draw(shader);
}

void Object::select(Shader shader)
{
	//selected = true;

	//draw(shader);
}

void Object::updateCenter()
{
	center.x = transform[3][0];
	center.y = transform[3][1];
	center.z = transform[3][2];
}