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

/* Source code for "Lighting" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */


#include <iostream>
#include <glut.h>

using namespace std;

void display(); 
void reshape(int, int);
void update(int);
void cube();

float _angle = -70.0f;

//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; 
GLfloat mat_shininess[] = { 60.0 }; 

//set world light
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

//light positions
GLfloat xlight0 = 0.0f ,ylight0 = 4.5f ,zlight0 = 0.0f;
GLfloat xlight1 = 4.0, ylight1 = 0.0, zlight1 = 0.0f;
GLfloat xlight2 = -4.0, ylight2 = 0.0, zlight2 = 0.0f;


//set Light #0
GLfloat light_position[] = { xlight0, ylight0, zlight0, 1.0 };
GLfloat light[] = { 1.0, 0.0, 0.0 };

//set Light #1
GLfloat light_position1[] = { xlight1, ylight1, zlight1, 1.0 };
GLfloat light1[] = { 0.0, 0.0, 1.0 };

//set Light #2
GLfloat light_position2[] = { xlight2, ylight2, zlight2, 1.0 };
GLfloat light2[] = { 0.0, 1.0, 0.0 };


//Emissions
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_emissionRed[] = {1.0, 0.0, 0.0, 1.0};
GLfloat mat_emissionBlue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat mat_emissionGreen[] = {0.0, 1.0, 0.0, 1.0};

//Initializes 3D rendering
void initRendering() {

	glClearColor(0.0,0.0,0.0,1.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}




int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Lighting - github.com/Jaeger47/Learning-OpenGL");
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

	//setting world lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting
	

	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display
	
	//RED LIGHT SOURCE
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glRotatef(_angle, 1.0f, 0.0f, 0.0f); //rotation animation
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light ); //add diffuse specular lighting
    glLightfv(GL_LIGHT0, GL_SPECULAR, light ); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionRed);
	glTranslatef(xlight0, ylight0, zlight0); //location
	glutSolidSphere(0.5,12,12);
	glPopMatrix();

	//BLUE LIGHT SOURCE
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);//add color material to object
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);//set light position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1 ); //add diffuse specular lighting
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1 ); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionBlue);
	glTranslatef(xlight1, ylight1, zlight1); //location
	glutSolidSphere(0.5,12,12);
	glPopMatrix();

	//GREEN LIGHT SOURCE
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);//add color material to object
	glRotatef(_angle, 1.0f, 1.0f, 1.0f); //rotation animation
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2 ); //add diffuse specular lighting
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2 ); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionGreen);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glutSolidSphere(0.5,12,12);
	glPopMatrix();


	//TEAPOT
	glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(0.9f, 0.9f, 0.9f);//add color material to object
	glTranslatef(0.0f, -1.0f, 0.0f); //location
	glRotatef(20, 1.0f, 0.0f, 0.0f); //rotation animation
	glutSolidTeapot (2);
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

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000/60, update, 0);
}

