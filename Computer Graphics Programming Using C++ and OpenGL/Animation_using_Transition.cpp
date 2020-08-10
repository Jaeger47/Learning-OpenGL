// Animation using Transition.cpp.cpp
//
// created by Mark Daniel G. Dacer at BukSU
// https://jaeger47.github.io/Learning-OpenGL/
//

#include <GL/glut.h>

void display();
void reshape(int,int);
void timer(int);

//primitive x position
float x_pos = 0;
//animation state
int state = 1;

void init()
{
	//set background to black
	glClearColor(0.0,0.0,0.0,1.0);
}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	//display modes
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//window postion
	glutInitWindowPosition(200,100);
	//window size
	glutInitWindowSize(500,500);

	//create the initialized window with name
	glutCreateWindow ("Basic Animation");

	//initialize display function
	glutDisplayFunc(display);
	//initialize reshape function
	glutReshapeFunc(reshape);
	//initialize timer function
	glutTimerFunc(0,timer,0); 
	init();

	//loop at the functions
	glutMainLoop();

}

void display()
{
	//clear color
	glClear(GL_COLOR_BUFFER_BIT);
	//clear transforms
	glLoadIdentity();

	//translate primitive position
	glTranslatef(x_pos,0,0);
	//creating a square primitive at the centre
	glBegin(GL_POLYGON);

	glVertex2f(1,1);
	glVertex2f(1,-1);
	glVertex2f(-1,-1);
	glVertex2f(-1,1);

	//end of primitive drawing
	glEnd();

	//swapbuffer to be displayed
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	//size of the world
	gluOrtho2D(-10,10,-10,10);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);

	//looping animation logic
	switch(state)
	{
	case 1:
		if(x_pos<10)
			x_pos+=0.15;
		else
			state = -1;
		break;
	case -1:
		if(x_pos>-10)
			x_pos-=0.15;
		else
			state=1;
		break;
	}
}
