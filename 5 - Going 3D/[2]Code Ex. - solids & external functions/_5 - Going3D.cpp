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

/* Source code for "Going3D" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */


#include <iostream>
#include <glut.h>

#include "primitives.h"

using namespace std;

void display(); 
void reshape(int, int);
void update(int);

float _angle = -70.0f;

//Initializes 3D rendering
void initRendering() {

	glClearColor(0.5f,0.0f,0.5f,1.0f); //set background to black
	glEnable(GL_DEPTH_TEST);

}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Going3D - github.com/Jaeger47/Learning-OpenGL");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}

//Draws the 3D scene
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display

	//pyramid
	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 0.0f);
	glRotatef(_angle, 1.0f, 0.0f, 0.0f);
	pyramid();
	glPopMatrix();
	//cube
	glPushMatrix();
	glTranslatef(-3.0f, 0.0f, 0.0f);
	glRotatef(_angle, 1.0f, 1.0f, 0.0f);
	cube();
	glPopMatrix();
	//teapot
	glPushMatrix();
	glTranslatef(-3.0f, 3.5f, 0.0f);
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidTeapot(1.5);
	glPopMatrix();
	//torus
	glPushMatrix();
	glTranslatef(3.0f, 3.5f, 0.0f);
	glRotatef(_angle, 0.0f, -1.0f, 0.0f);
	glColor3f(0.2f, 0.02f, 0.2f);
	glutSolidTorus(0.5f,0.8f,12.0f,24.0f);
	glPopMatrix();
	//wireframe sphere
	glPushMatrix();
	glTranslatef(3.0f, -3.5f, 0.0f);
	glRotatef(_angle, 0.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireSphere(1.5,12,24);
	glPopMatrix();
	//wireframe icosahedron
	glPushMatrix();
	glTranslatef(-3.0f, -3.5f, 0.0f);
	glRotatef(_angle, 1.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireIcosahedron();
	glPopMatrix();

	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//rotation animation logic
void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000/60, update, 0);
}




