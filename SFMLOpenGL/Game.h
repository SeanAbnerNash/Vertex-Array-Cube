#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Matrix3.h"

using namespace std;
using namespace sf;
//@Author Sean Nash De Andrade
//@Login C00217019
//Cube Rotation Assignment

class Game
{
public:
	Game();
	~Game();
	void run();
	bool m_changed;//If the Matrix has been changed
	Matrix3 m_Matrix;//Transformation Matrix
	void arraySetup();//Sets up the Tranformable Array
	void updateVertices();//Applies current co ordinates to the Open GL Float Array 
	void transformVertices();//Transforms Vertices by tranformation matrix
private:
	Window window;
	MyVector3 m_transformableVertex[8];//Array to Hold transformable values for Array
	float m_vertexArray[24];//Array to hold the co ordinates in a format Open GL can use
	float m_vertColourArray[24] = { 
		0.0f, 0.0f, 1.0f,//Vertex 0 Colour
		0.0f, 1.0f, 0.0f,//Vertex 1 Colour
		1.0f, 0.0f, 0.0f,//Vertex 2 Colour
		1.0f, 1.0f, 1.0f,//Vertex 3 Colour

		0.0f, 0.0f, 0.0f,//Vertex 4 Colour
		1.0f, 0.0f, 1.0f,//Vertex 5 Colour
		0.0f, 1.0f, 1.0f,//Vertex 6 Colour
		1.0f, 1.0f, 0.0f//Vertex 7 Colour

	};
	unsigned int vertex_index[36] = {
		0, 1, 2, //Triangle 0 Side 1
		0, 2, 3,//Triangle 1 Side 1
		4, 5, 6,//Triangle 0 Side 2
		4, 6, 7,//Triangle 1 Side 2
		4, 5, 1, //Triangle 0 Side 3
		4, 1, 0,//Triangle 1 Side 3
		7, 6, 2, //Triangle 0 Side 4
		7, 2, 3,//Triangle 1 Side 4
		4, 0, 3, //Triangle 0 Side 5
		4, 3, 7,//Triangle 1 Side 5
		1, 5, 6,//Triangle 0 Side 6
		1, 6, 2 //Triangle 1 Side 6
	};


	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

};