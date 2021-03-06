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


float anguloTriangulo = 0.0f;
float anguloTrayectoria = 0.0f;
float velocidadAngular = 100;

float velocidad = 0.7f;
float aceleracion = 0.8f;
float desaceleracion = 0.4f;
float velocidadActual = 0.0f;

float xCuadrado = -0.4f;
float yCuadrado = -0.5f;

float angulo = 0.0f;

double tiempoAnterior = 0.0;
double tiempoActual = 0.0;
double tiempoDiferencial = 0.0;

float rTriangulo = 1.0f;
float gTriangulo = 1.0f;
float bTriangulo = 1.0f;


//Declaramos apuntador de ventana
GLFWwindow *window;

void dibujarCuadrado() {
	glPushMatrix();
	//Transoformaciones
	glTranslatef(xCuadrado, yCuadrado, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(9.0f, 0.3f, 0.4f);
	glVertex3f(-0.1f, 0.1f, 0);
	glVertex3f(-0.1f, -0.1f, 0);
	glVertex3f(0.1f, -0.1f, 0);
	glVertex3f(0.1f, 0.1f, 0);
	glEnd();

	glPopMatrix();
}



void dibujarTriangulo() {

	//Utilizar matris identidad
	glPushMatrix();
	//Transformacion
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotatef(anguloTriangulo, 0.0f, 0.0f, 1.0f);
	
	//dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(rTriangulo, gTriangulo, bTriangulo);
	glVertex3f(0.0f, 0.08f, 0);
	glVertex3f(-0.05f, -0.08f, 0);
	glVertex3f(0.05f, -0.08f, 0);
	glEnd();

	//soltar la matriz
	glPopMatrix();

}


void dibujar() {
	dibujarTriangulo();
	dibujarCuadrado();
}


void moverTriangulo() {

	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoTeclaDerecha == GLFW_PRESS)
	{
		anguloTriangulo -= velocidadAngular * tiempoDiferencial;
		if (anguloTriangulo < 0)
		{
			anguloTriangulo += 360;
		}
	}
	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoTeclaIzquierda == GLFW_PRESS)
	{
		anguloTriangulo += velocidadAngular * tiempoDiferencial;
		if (anguloTriangulo >= 90)
		{
			anguloTriangulo -= 360;
		}
	}
	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoTeclaArriba == GLFW_PRESS)
	{
		anguloTrayectoria = anguloTriangulo;
		if (velocidadActual <= velocidad)
		{
			velocidadActual += aceleracion * tiempoDiferencial;
		}
	}
	else 
	{
		if (velocidadActual >= 0)
		{
			velocidadActual -= desaceleracion * tiempoDiferencial;
			if (velocidadActual < 0)
			{
				velocidadActual = 0.0f;
			}
		 }
	}

	posicionXTriangulo += cos((anguloTrayectoria + 90.0f)* 3.14159f / 180.0f) * velocidadActual * tiempoDiferencial;

	if (posicionXTriangulo < -1.1f)
	{
		posicionXTriangulo += 2;
	}
	else if (posicionXTriangulo > 1.1f)
	{
		posicionXTriangulo -= 2;
	}


	posicionYTriangulo += sin((anguloTrayectoria + 90.0f) * 3.14159f / 180.0f) * velocidadActual * tiempoDiferencial;
	
	if (posicionYTriangulo < -1.1f)
	{
		posicionYTriangulo += 2;
	}
	else if (posicionYTriangulo > 1.1f)
	{
		posicionYTriangulo -= 2;
	}

}

void checarColisiones() {
	//Si el triangulo colisiona con el cuadrado
	if (posicionXTriangulo - 0.2f < xCuadrado + 0.1f && posicionXTriangulo + 0.2 > xCuadrado - 0.1f
		&& posicionYTriangulo - 0.2f < yCuadrado + 0.1f && posicionYTriangulo + 0.2f > yCuadrado - 0.1f) {
		gTriangulo = 0.0f;
		bTriangulo = 0.0f;

		xCuadrado = (rand() % 2) - 1;
		yCuadrado = (rand() % 2) - 1;
	}
	else {
		gTriangulo = 1.0f;
		bTriangulo = 1.0f;
	}

}

void actualizar() {
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;

	moverTriangulo();
	checarColisiones();
	tiempoAnterior = tiempoActual;
}

void teclado_calback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		posicionXTriangulo +=  velocidad;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		posicionXTriangulo -= velocidad;
	}

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		posicionYTriangulo += velocidad;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		posicionYTriangulo -= velocidad;
	}

}



int main()
{
	

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


	//glfwSetKeyCallback(window, teclado_calback);

	tiempoAnterior = glfwGetTime() ;


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

