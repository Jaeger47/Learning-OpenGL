/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *

/* Source code for "Colour" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */


#include <iostream>
#include <glut.h>

using namespace std;

void display();
void reshape(int,int);
void update(int);

float angle = 0; //rotation angle


void init()
{
	
	glClearColor(0.3,0.3f,0.3f,1.0f); //set background to black
	
}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //display modes
	
	glutInitWindowPosition(200,100); //window postion
	glutInitWindowSize(500,500); //window size
	glutCreateWindow ("Colour - github.com/Jaeger47/Learning-OpenGL"); //create the initialized window with name
	
	glutDisplayFunc(display); //initialize display function
	glutReshapeFunc(reshape); //initialize reshape function
	
	init();

	glutTimerFunc(1000/60,update,0); //add timer

	glutMainLoop();//loop at the functions

}

void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT);//clear color
	
	glLoadIdentity();//clear transforms

	glPushMatrix(); 
	glTranslatef(5.0f, 5.0, 0.0f); // move object from origin
	glRotatef(angle, 0.0f, 0.0f, 1.0f); //animated rotation
	
	//draw triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); //red
		glVertex2f(-2.0f, -2.0f);
		glColor3f(0.0f, 1.0f, 0.0f); //green
		glVertex2f(2.0f, -2.0f);
		glColor3f(0.0f, 0.0f, 1.0f); //blue
		glVertex2f(0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f, 5.0, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	//draw square
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 1.0f); //cyan
		glVertex2f(-2.0f, -2.0f);
		glVertex2f(2.0f, -2.0f);
		glVertex2f(2.0f, 2.0f);
		glVertex2f(-2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -5.0, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	//draw pentagon
	glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 1.0f); //magenta
		glVertex2f(-1.0f, -2.0f);
		glVertex2f(1.0f, -2.0f);
		glVertex2f(2.0f, 1.0f);
		glVertex2f(0.0f, 3.0f);
		glVertex2f(-2.0f, 1.0f);
	glEnd();
	glPopMatrix();
	
	glutSwapBuffers(); //Send the scene to the screen
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10,10,-10,10);//size of the world
	glMatrixMode(GL_MODELVIEW);
}

void update(int)
{


	//looping animation logic
	angle+=0.8;
	if(angle>360.0f)
		angle=angle-360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000/60,update,0);

}
