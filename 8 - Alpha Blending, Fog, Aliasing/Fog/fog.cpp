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

/* Source code for "Fog" by Mark Daniel G. Dacer
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
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light[] = { 0.5, 0.5, 0.5 };
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };


static GLint fogMode; //fog mode declaration


//Initializes 3D rendering
void initRendering() {

	glClearColor(0.0,0.0,0.0,1.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	 glEnable(GL_FOG);
   {
      GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0}; //foreground fog color

      fogMode = GL_EXP; //fog mode algo
      glFogi (GL_FOG_MODE, fogMode);
      glFogfv (GL_FOG_COLOR, fogColor);
      glFogf (GL_FOG_DENSITY, 0.03);  //density of fog 
	  glHint (GL_FOG_HINT, GL_NICEST);
	  //fog distance
      glFogf (GL_FOG_START, 1.0);
      glFogf (GL_FOG_END, 5.0);
   }
   glClearColor(0.5, 0.5, 0.5, 1.0);  /* background fog color */

	
}




int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Fog - github.com/Jaeger47/Learning-OpenGL");
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
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light ); //add diffuse specular lighting
    glLightfv(GL_LIGHT0, GL_SPECULAR, light ); //add specular lighting
	
	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display
	
	glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glColor3f(0.0f, 1.0f, 0.0f);//add color material to object
	glTranslatef(3.0f, 0.0f, 0.0f); //location
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
	glutSolidTeapot (1.5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set object shininess 
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glTranslatef(-3.0f, 0.0f, 0.0f); //location
	glRotatef(_angle, 1.0f, 0.0f, 0.0f); //rotation animation
	glutSolidTorus(0.5,1,24,48);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set object shininess 
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glTranslatef(0.0f, 3.0f, 0.0f); //location
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
	cube();
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


//cube
void cube(){
	glBegin(GL_QUADS);
		//front
		glColor3f(1.0f,0.0f,0.0f); //red
		glNormal3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		//right
		glColor3f(0.0f,1.0f,0.0f); //green
		glNormal3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glVertex3f(1.0f, 1.0f, 0.0f);

		//back
		glColor3f(0.0f,0.0f,1.0f); //blue
		glNormal3f(0.0f,0.0f,-1.0f);
		glVertex3f(-1.0f, -1.0f, -1.5f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glVertex3f(-1.0f, 1.0f, -1.5f);

		//left
		glColor3f(1.0f,1.0f,0.0f); //yellow
		glNormal3f(-1.0f,0.0f,0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.5f);
		glVertex3f(-1.0f, 1.0f, -1.5f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		//top
		glColor3f(0.0f,1.0f,1.0f); //cyan
		glNormal3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glVertex3f(-1.0f, 1.0f, -1.5f);

		//bottom
		glColor3f(0.0f,0.0f,0.0f); //black
		glNormal3f(0.0f,-1.0f,0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glVertex3f(-1.0f, -1.0f, -1.5f);
	glEnd();

}