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

/* Source code for "Anti-aliasing" by Mark Daniel G. Dacer
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
	
	glClearColor(0.0,0.0f,0.0f,1.0f); //set background to black
	
	glEnable(GL_LINE_STIPPLE); //enable style
	glEnable (GL_LINE_SMOOTH); //line aliasing
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);//setting aliasing
	
}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //display modes
	
	glutInitWindowPosition(200,100); //window postion
	glutInitWindowSize(500,500); //window size
	glutCreateWindow ("Anti-aliasing - github.com/Jaeger47/Learning-OpenGL"); //create the initialized window with name
	
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
	glLineWidth(15.0f);
	glLineStipple(3, 0x00FF);
	
   glColor3f (0.0, 1.0, 0.0);
   glPushMatrix();
   glRotatef(-angle, 0.0, 0.0, 0.1);

   glBegin (GL_LINES);
      glVertex2f (-6.5f, 6.5f);
      glVertex2f (6.5f, -6.5f);
   glEnd ();
   
   glPopMatrix();

   glColor3f (0.0, 0.0, 1.0);
   glPushMatrix();
   glRotatef(angle, 0.0, 0.0, 0.1);
   
   glBegin (GL_LINES);
      glVertex2f (6.5f, 6.5f);
      glVertex2f (-6.5f, -6.5f);
   glEnd ();
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
