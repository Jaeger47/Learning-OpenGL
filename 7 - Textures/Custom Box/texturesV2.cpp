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
void reshape(int, int);
void display();
void loadTexture(const char *, GLuint);

GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat directedLightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };

float angle = 0; //rotation angle
GLuint textures[1]; // Array to store texture IDs

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	loadTexture("vtr.bmp", textures[0]); //load image file 8-32bit .jpg, .png, .bmp
	//optimal size 256x256, 512x512, 1024x1024
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(400, 400);

	glutCreateWindow("Textures - github.com/Jaeger47/Learning-OpenGL");
	initRendering();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / 60, update, 0); //add timer
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
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glRotatef(angle, 1, 1, 0);
	
	glBegin(GL_QUADS);//start of the primitive
		//front
		glNormal3f(0.0f, 0.0f, 1.0f); //normal map
			glTexCoord2f(0.0f, 0.0f); //texture coordinate
				glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, 0.0f);

		//right
		glNormal3f(1.0f, 0.0f, 0.0f); //normal map
			glTexCoord2f(0.0f, 0.0f); //texture coordinates
				glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -1.5f);
				glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, 0.0f);

		//back
		glNormal3f(0.0f, 0.0f, -1.5f); //normal map
			glTexCoord2f(0.0f, 0.0f); //texture coordinates
				glVertex3f(-1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -1.5f);
				glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.5f);

		//left
		glNormal3f(-1.0f, 0.0f, 1.0f); //normal map
			glTexCoord2f(0.0f, 0.0f); //texture coordinates
				glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -1.5f);
				glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, 0.0f);

		//top
		glNormal3f(0.0f, 1.0f, 0.0f); //normal map
			glTexCoord2f(0.0f, 0.0f); //texture coordinates
				glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.5f);

		//bottom
		glNormal3f(0.0f, -1.0f, 0.0f); //normal map
			glTexCoord2f(0.0f, 0.0f); //texture coordinates
				glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, -1.5f);
		
	glEnd();//end of the primitive

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}



void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}


void update(int)
{
	//looping animation logic
	angle += 0.8f;
	if (angle > 360.0f)
		angle = angle - 360.0f;
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);

}

void loadTexture(const char *filename, GLuint textureID) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//change GL_RGB to GL_RGBA for blending
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture: %s\n", filename);
    }
}
