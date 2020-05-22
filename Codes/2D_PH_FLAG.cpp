#include <GL/glut.h>

void display();
void reshape(int,int);
void timer(int);

void init()
{
	glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
}


int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowPosition(200,200);
	glutInitWindowSize(400,400);
	glutCreateWindow("Window");
	 

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	init();

	glutMainLoop();

}


void display()
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//SUN
	glPointSize(10.0);
	glBegin(GL_POINTS);
    glColor4f(2.0,2.0,0.0,0.7);
    glVertex2f(-3.0,0.0);
	glEnd();

	//WHITE 
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(-4.0,2.0);
    glVertex2f(-4.0,-2.0);
    glVertex2f(0.0,0.0);
	glEnd();

	//BLUE
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.0,1.0);
    glVertex2f(-4.0,2.0);
    glVertex2f(-4.0,0.0);
    glVertex2f(3.0,0.0);
    glVertex2f(3.0,2.0);
	glEnd();

    //RED
	glLoadIdentity();
	glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(-4.0,0.0);
    glVertex2f(-4.0,-2.0);
    glVertex2f(3.0,-2.0);
    glVertex2f(3.0,0.0);
	glEnd();

	//POLE
	glLoadIdentity();
	glBegin(GL_POLYGON);
    glColor3f(0.5,0.5,0.5);
    glVertex2f(-4.0,-2.0);
    glVertex2f(-4.0,-9.0);
    glVertex2f(-3.0,-9.0);
    glVertex2f(-3.0,-2.0);
	glEnd();

	//GROUND
	glLoadIdentity();
	glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.3);
    glVertex2f(-15.0,-9.0);
    glVertex2f(-15.0,-15.0);
    glVertex2f(15.0,-15.0);
    glVertex2f(15.0,-9.0);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-15,15,-15,15);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);

}