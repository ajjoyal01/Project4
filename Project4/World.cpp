#include "World.h"

World::World()
{
	srand(time(NULL));

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
	//setupTextures(); 
	
	// Antialiasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glLineWidth(4);

	glEnable(GL_DEPTH_TEST);

	game.init();
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
			game.playTurn();
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

	//now draw the scene
	/*
	for (int i = 0; i < NUM_OBJECTS;i++)
	{
		objects[i]->draw();
	}*/

	game.draw(_shader);

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
}

void World::setupTextures()
{
	
	// Texture Files
	_textureFilenames[0] = "Textures/all-cards.png";
	_textureFilenames[1] = "Textures/table.png";

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		_textures[i] = new Texture();
		_textures[i]->loadFromFile(_textureFilenames[i]);
	}
}
