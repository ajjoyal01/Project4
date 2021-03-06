#include "World.h"

World::World()
{
	srand(time(NULL));

	sequenceTest = 0;

	axes = new Axes();
	drawAxes = false;

	// Lighting parameters
	_directionalColor = { 0.9, 0.9, 0.9 };
	_ambientColor = { 0.5, 0.5, 0.5 };
	_lightStrength = 2.0;
	_lightShinniness = 3.0;
	_lightDirection = vmath::vec3(.5, .5, 1.0);
}

World::~World()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete _textures[i];
	}
}

void World::init()
{
	initValues();
	_cam.init();
	_shader.init(); 

	
	// Antialiasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glLineWidth(3);

	glEnable(GL_DEPTH_TEST);
	game.init();
	setupTextures();
}

void World::display()
{
	// clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw world
	draw();

	// swap the buffers at the end of the display sequence
	glutSwapBuffers();
}

void World::keyPress(unsigned char key,int x,int y)
{
	switch (key)
	{
	case 'n':
		if (game.getWinner() == 0)
		{
			if (sequenceTest == 0)
			{
				cout << "Flip\n";
				game.playTurn1();
				sequenceTest = (sequenceTest + 1) % 2;
			}	
			else
			{
				cout << "Discard\n";
				game.playTurn2();
				sequenceTest = (sequenceTest + 1) % 2;
			}
		}
		
		break;
	case 'l':
		_light.toggle();
		break;
	case 'i':
		_cam.camIn(CAM_MOVE);
		break;
	case 'o':
		_cam.camOut(CAM_MOVE);
		break;
	case 'q':
		drawAxes = !drawAxes;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void World::arrowInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		_cam.camUp(CAM_MOVE);
		break;
	case GLUT_KEY_DOWN:
		_cam.camDown(CAM_MOVE);
		break;
	case GLUT_KEY_LEFT:
		_cam.camLeft(CAM_MOVE);
		break;
	case GLUT_KEY_RIGHT:
		_cam.camRight(CAM_MOVE);
		break;
	}

	glutPostRedisplay();
}

void World::draw()
{
	// setup lighting uniforms
	_light.render(_shader);

	// setup camera uniforms
	_cam.render(_shader);

	if (drawAxes)
		axes->draw(_shader);

	_textures[0]->load();
	game.draw(_shader);

	//room.draw(_shader);
	_textures[1]->load();
	table.draw(_shader);
}

void World::initValues()
{
	// init light values
	_light.setColor(_directionalColor);
	_light.setAmbient(_ambientColor);
	_light.setDirection(_lightDirection);
	_light.setShininess(_lightShinniness);
	_light.setStrength(_lightStrength);
	_light.toggle();

	//----------------------------------------------------------
	// Data for Axes
	//----------------------------------------------------------
	vec4 axesPosition[NUM_AXES][2] = {
			{ vec4(-5.0, 0.0, 0.0, 1.0), vec4(5.0, 0.0, 0.0, 1.0) },
			{ vec4(0.0, -5.0, 0.0, 1.0), vec4(0.0, 5.0, 0.0, 1.0) },
			{ vec4(0.0, 0.0, -5.0, 1.0), vec4(0.0, 0.0, 5.0, 1.0) }
	};

	Color axesColor = { .8, .8, .8, 1 };
	Color roomColor = { 1, .3, 0, 1 };

	axes->init(axesPosition);
	axes->setColor(axesColor);

	room.init("Models/room1.obj");
	room.setColor(roomColor);

	table.init("Models/table.obj");
	table.setColor(roomColor);
	table.translate(0, -0.2, -0.3);

}

void World::setupTextures()
{
	
	// Texture Files
	_textureFilenames[0] = "Textures/all_cards.png";
	_textureFilenames[1] = "Textures/table.png";

	for (int i = 0; i < 2; i++)
	{
		_textures[i] = new Texture();
		_textures[i]->loadFromFile(_textureFilenames[i]);
	}
	game.master.setTexture(_textures[0]);
	table.setTexture(_textures[1]);
	_textures[0]->load();
}
