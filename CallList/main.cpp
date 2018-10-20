#include<GL/freeglut.h>
#include<iostream>

const int LARGURA=800;
const int ALTURA=600;
const int TRIANGULO=1;


float red[]={1,0,0};
float green[]={0,1,0};
float blue[]={0,0,1};

void desenha();
void criarTriangulo();
void inicia3D();
void teclado(unsigned char key,int x, int y);
void move(int valor);

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Universidade Federal de Rondonopolis - Glut Texture");

	inicia3D();
	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);


	glutMainLoop();
	return 0;
}


void desenha()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0,0,-5);
	glCallList(TRIANGULO);

	glutSwapBuffers();

}
void criarTriangulo()
{
  glNewList(TRIANGULO,GL_COMPILE);
        glBegin(GL_TRIANGLES);
            glColor3fv(red);
            glVertex3f(0,2,0);
            glColor3fv(green);
            glVertex3f(-2,-2,0);
            glColor3fv(blue);
            glVertex3f(2,-2,0);
        glEnd();
	glEndList();
}


void inicia3D()
{

	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(double)LARGURA/ALTURA,1,500);
	glMatrixMode(GL_MODELVIEW);

	criarTriangulo();
    glEnable(GL_DEPTH_TEST);
}


void teclado(unsigned char key,int x, int y)
{
	switch (key)
	{
		case 27: //Esc
			exit(0);

	}
}
