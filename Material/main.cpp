#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include "objloader.h"

using std::cout;

const int LARGURA=800;
const int ALTURA=600;
const int FPS=35;

float ang=0;
int objeto;
objloader obj;

void desenha();
void inicia3D();
void teclado(unsigned char key,int x, int y);
void move(int valor);

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Universidade Federal de Rondonopolis - Prof.Sergio Silva");

	inicia3D();

	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);
	glutTimerFunc(1000/FPS,move,0);

	glutMainLoop();
	return 0;
}

void move(int valor)
{
	ang+=0.5;
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,move,0);
}

void desenha()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	float pos[]={2,2,5,1};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);

	glTranslatef(0,0,-15);
	glRotatef(ang,1,1,0);

	glCallList(objeto);

	glutSwapBuffers();

}

void inicia3D()
{

	glClearColor(0,0,0,1);
	//glClearColor(0.6,0.6,0.6,1);//FOG Color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(double)LARGURA/ALTURA,1.0,500);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float color[]={1,1,1,1};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,color);

	//objeto=obj.carrega("C:\\Users\\Sergio\\Documents\\DLL\\CODEBLOCK\\GLUT\\Material\\ADON.obj");
	//objeto=obj.carrega("C:\\Users\\Sergio\\Documents\\DLL\\CODEBLOCK\\GLUT\\Material\\monkey.obj");
	objeto=obj.carrega("C:\\Users\\Sergio\\Documents\\DLL\\CODEBLOCK\\GLUT\\Material\\cuboMaterial.obj");

}


void teclado(unsigned char key,int x, int y)
{
	switch (key)
	{
		case 27: //Esc
			exit(0);

	}
}
