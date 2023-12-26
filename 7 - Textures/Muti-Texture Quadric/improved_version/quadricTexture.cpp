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
 */
/* Source code for "Textures" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <gl/glut.h>
#include "stb_image.h"

void update(int);
void loadTexture();
void reshape(int, int);
void display();

GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat directedLightPos[] = {0.0f, 0.0f, 1.0f, 0.0f};

float angle = 0; //rotation angle

GLuint earTex, pepTex; // Array to store texture IDs

GLUquadric *ball; //pointer quadric shape for the sphere
GLUquadric *can; //pointer quadric shape for the cylinder

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	loadTexture();
	ball = gluNewQuadric(); //declared as quadric objects
	can = gluNewQuadric(); //declared as quadric objects

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("Textures - github.com/Jaeger47/Learning-OpenGL");
	initRendering();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000/60,update,0); //add timer
	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	glPushMatrix(); 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	
	glEnable(GL_TEXTURE_2D);

	////--------EARTH---------------------------------------------------///
	glBindTexture(GL_TEXTURE_2D, earTex);
	
	
	gluQuadricTexture(ball,1);
	
	glPushMatrix();
	glTranslatef(-1.5f, 0.0f, 0.0f);
	glRotatef(-270,1.0f, 0.0f, 0.0f);
	glRotatef(angle,0.0f, 0.0f, 1.0f); //animated rotation
	gluSphere(ball,1.25,24,24);
	glPopMatrix();
	////--------EARTH---------------------------------------------------///


	////--------PEPSI CAN---------------------------------------------------///
	glBindTexture(GL_TEXTURE_2D, pepTex);

	gluQuadricTexture(can,1);

	glPushMatrix();
	glTranslatef(1.5f, 1.0f, 0.0f);
	glRotatef(-270,1.0f, 0.0f, 0.0f);
	glRotatef(angle,0.0f, 0.0f, -1.0f); //animated rotation
	gluCylinder(can,0.7,0.7,2,24,24);
	glPopMatrix();
	////--------PEPSI CAN---------------------------------------------------///


	glDisable(GL_TEXTURE_2D); 
	
	
	
	glutSwapBuffers();
}

//Makes the image into a texture
void loadTexture() {
    int width, height, nrChannels;
    unsigned char *data = stbi_load("aarth.bmp", &width, &height, &nrChannels, 0);
		
		glGenTextures(1, &earTex);
        glBindTexture(GL_TEXTURE_2D, earTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//change GL_RGB to GL_RGBA for blending
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load("pepsi.bmp", &width, &height, &nrChannels, 0);

		glGenTextures(1, &pepTex);
        glBindTexture(GL_TEXTURE_2D, pepTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//change GL_RGB to GL_RGBA for blending
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      stbi_image_free(data);

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 200.0);
}


void update(int)
{


	//looping animation logic
	angle+=2;
	if(angle>360.0f)
		angle=angle-360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000/60,update,0);

}





