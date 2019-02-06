// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include<iostream>

using namespace std;

float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float velocidad = 0.05f;

float angulo = 0.0f;




void dibujarTriangulo() {

	//Utilizar matris identidad
	glPushMatrix();
	//Transformacion
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotated(angulo, 1.0f, 1.0f, 1.0f);
	//dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);
	glEnd();

	//soltar la matriz
	glPopMatrix();

}


void dibujar() {
	dibujarTriangulo();

}

void actualizar() {
	
}

void teclado_calback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		posicionXTriangulo +=  velocidad;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		posicionXTriangulo -= velocidad;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		posicionYTriangulo += velocidad;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		posicionYTriangulo -= velocidad;
	}

}

int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//Si no se pudo iniciar glfw
	//terminamos ejecución 
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	//Si se pudo inciar GLFW
	//Entonces inicializamos la ventana

	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana 
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecer el contexto
	glfwMakeContextCurrent(window);


	//Una vez establecido el contexto
	//Activamos fnciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK)
	{
		cout << glewGetErrorString(errorGlew);

	}


	const GLubyte *versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: "
		<< versionGL;


	glfwSetKeyCallback(window, teclado_calback);

	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0,1024, 768);
		//Establecer el color de orrado
		glClearColor(0.5, 0.4, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

