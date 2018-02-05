#include "Game.h"
//@Author Sean Nash De Andrade
//@Login C00217019
//Cube Array Assignment
bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Vertex Array Cube")
{
 arraySetup();
}

Game::~Game() {}


void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::arraySetup()
{
	 m_transformableVertex[0] = MyVector3(1.0f, 1.0f, 1.0f);//Front Side Top Right Corner
		m_transformableVertex[1] = MyVector3(-1.0f, 1.0f, 1.0f);//Front Side Bottom Right Corner
		m_transformableVertex[2] = MyVector3(-1.0f, -1.0f, 1.0f);//Front Side Bottom Left Corner
		m_transformableVertex[3] = MyVector3(1.0f, -1.0f, 1.0f); //Front Side Top Left Corner

		m_transformableVertex[4] = MyVector3(1.0f, 1.0f, -1.0f);//Back Side Top Right Corner
		m_transformableVertex[5] = MyVector3(-1.0f, 1.0f, -1.0f);//Back Side Bottom Right Corner
		m_transformableVertex[6] = MyVector3(-1.0f, -1.0f, -1.0f);//Back Side Top Left Corner
		m_transformableVertex[7] = MyVector3(1.0f, -1.0f, -1.0f);//Back Side Bottom Left Corner


}

void Game::updateVertices()
{
	int temptIndex = 0;
	for (int i = 0; i < 8; i++)
	{
		temptIndex = i * 3;
		m_vertexArray[temptIndex] = m_transformableVertex[i].getX();//Applies the individual components of the tranformable vertices into the OpenGl Array
		m_vertexArray[temptIndex + 1] = m_transformableVertex[i].getY();//The OpenGL array stores the co ordinates in a way OpenGL can use
		m_vertexArray[temptIndex + 2] = m_transformableVertex[i].getZ();
	}
}

void Game::transformVertices()
{
	for (int i = 0; i < 8; i++)
	{
		m_transformableVertex[i] = m_transformableVertex[i] * m_Matrix;//Applies the transformation matrix to all transformable Vertices
	}
}

void Game::initialize()
{
	isRunning = true;

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//Clears the screen white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 510.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -10.0f);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//Rotates Right
	{
		m_changed = true;
		m_Matrix = m_Matrix.Rotation(1);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//Rotates Left
	{
		m_changed = true;
		m_Matrix = m_Matrix.Rotation(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//Moves Right
	{
		m_changed = true;
		m_Matrix = m_Matrix.Translate(0.001, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//Moves Left
	{
		m_changed = true;
		m_Matrix = m_Matrix.Translate(-0.001, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))//Scales Down
	{
		m_changed = true;
		m_Matrix = m_Matrix.Scale(99.5, 99.5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))//Scales Up
	{
		m_changed = true;
		m_Matrix = m_Matrix.Scale(100.5, 100.5);
	}
	
	if (m_changed == true)
	{
		m_changed = false;
		transformVertices();
	}
	updateVertices();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clears previous drawings
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &m_vertexArray);//Sets the array start points
	glColorPointer(3, GL_FLOAT, 0, &m_vertColourArray);
		

	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, &vertex_index);//Draws the Triangles, Index tells which vertex  to use in what order.

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();//Display

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

