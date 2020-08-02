#include <GL/glut.h>

void display();
void reshape(int,int);
void timer(int);
void key(int,int,int);


float shift_x = 0;
float shift_y = 0;
void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	glutSpecialFunc(key);
	init();

	glutMainLoop();

}


void display()
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f + shift_x, 0.0f + shift_y ,0.0);

	glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.3);
    glVertex2f(-5 /*+ shift_x*/ ,-5 /*+ shift_y */);
    glVertex2f(-5 /*+ shift_x*/ ,5 /*+ shift_y */);
    glVertex2f(5 /*+ shift_x*/ ,5 /*+ shift_y */);
    glVertex2f(5 /*+ shift_x*/ ,-5 /*+ shift_y */);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-20,20,-20,20);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);

}

void key(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		shift_x--;
		glutPostRedisplay();
		glutTimerFunc(1000/60,timer,0);
		break;
	case GLUT_KEY_RIGHT:
		shift_x++;
		glutPostRedisplay();
		glutTimerFunc(1000/60,timer,0);
		break;
	case GLUT_KEY_UP:
		shift_y++;
		glutPostRedisplay();
		glutTimerFunc(1000/60,timer,0);
		break;
	case GLUT_KEY_DOWN:
		shift_y--;
		glutPostRedisplay();
		glutTimerFunc(1000/60,timer,0);
		break;

	}
}
