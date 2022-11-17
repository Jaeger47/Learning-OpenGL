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
/* Source code for "Blending" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */

#include <iostream>
#include <string>
#include <gl/glut.h>

using namespace std;

#include "imageloader.h"

void update(int);
GLuint loadTexture(Image* image);
void reshape(int, int);
void display();
void processNormalKeys(unsigned char, int , int);
void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string);


float angle = 0; //rotation angle

GLuint _textureId; //The id of the texture

int counterS = 1;
int countArrS = 0;
int counterD = 1;
int countArrD = 0;

float opacity = 0.25;
int opacityCount = 1;

//add replace char * to const char * if getting errors
char *sFactorStr[][10] = {"GL_ONE","GL_ZERO", "GL_DST_COLOR", "GL_ONE_MINUS_DST_COLOR", 
	"GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA", "GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE", " "};

char *dFactorStr[][9] = {"GL_ZERO", "GL_ONE", "GL_SRC_COLOR", "GL_ONE_MINUS_SRC_COLOR",
	"GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA", "GL_ONE_MINUS_DST_ALPHA", " "};

char *OpacityStr[][6] = {"0.00","0.25", "0.50", "0.75", "1.00", " "};

GLenum sFactor[] = {GL_ONE, GL_ZERO, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, 
	GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE};

GLenum dFactor[] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
	GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};



void initRendering() {
	glClearColor(0.4, 0.3, 0.3, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glEnable (GL_BLEND);

	//glDepthMask(GL_FALSE); disabled to work
    glBlendFunc(GL_ONE, GL_ZERO); //default

	Image* image = loadBMP("vtr.bmp");
	_textureId = loadTexture(image);
	delete image;


}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Textures - github.com/Jaeger47/Learning-OpenGL");
	initRendering();
	glutKeyboardFunc(processNormalKeys);//controls
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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//glRotatef(270, 1.0f, 0.0f, .0f); 
	
	glColor4f(0.0f,1.0f,0.0f,1.0); 
	glPushMatrix();
	glTranslatef(0,0,-3);
	glRotatef(angle,1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.5,1,24,24);
	glPopMatrix();

  glRotatef(angle,0.0f, 1.0f, 0.0f); //animated rotation
	glBegin(GL_QUADS);

		glColor4f(1.0f,1.0f,1.0f,opacity); 
		//front
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		//right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);

		//back
		glNormal3f(0.0f, 0.0f, -1.5f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);

		//left
		glNormal3f(-1.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		//top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);

		//bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.5f);
		
	glEnd();
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix(); 
	
	glDisable(GL_BLEND);
	glColor4f(1,1,1,1);
	//add (char *) befre the string if getting errors
	renderBitmapString(-1.6f, 1.1f, 2.0f, GLUT_BITMAP_HELVETICA_18,"Foreground: ");
	renderBitmapString(-1.0f, 1.1f, 2.0f, GLUT_BITMAP_HELVETICA_18,sFactorStr[0][countArrS]);
	renderBitmapString(-1.6f, 1.0f, 2.0f, GLUT_BITMAP_HELVETICA_18,"Background: ");
	renderBitmapString(-1.0f, 1.0f, 2.0f, GLUT_BITMAP_HELVETICA_18,dFactorStr[0][countArrD]);
	renderBitmapString(1.4f, -1.2f, 2.0f, GLUT_BITMAP_HELVETICA_18, OpacityStr[0][opacityCount]);
	renderBitmapString(1.1f, -1.2f, 2.0f, GLUT_BITMAP_HELVETICA_18, "Alpha: ");

	renderBitmapString(-1.6f, -1.0f, 2.0f, GLUT_BITMAP_HELVETICA_12, "Press 1 - 5 to change alpha level");
	renderBitmapString(-1.6f, -1.1f, 2.0f, GLUT_BITMAP_HELVETICA_12,"Press Q to change Foreground parameter");
	renderBitmapString(-1.6f, -1.2f, 2.0f, GLUT_BITMAP_HELVETICA_12,"Press E to change Background parameter");
	glEnable(GL_BLEND);
	
	
	glutSwapBuffers();
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
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
	angle+=2;
	if(angle>360.0f)
		angle=angle-360.0f;
	
	glutPostRedisplay();
	glutTimerFunc(1000/60,update,0);

}

//keyboard controls
void processNormalKeys(unsigned char key, int x, int y) {
	float fraction = 1.5f;
	

	switch(key){
		case 'q':
			counterS = counterS + 1;
			if(counterS == 1){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 2){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 3){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 4){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 5){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 6){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 7){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 8){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}
			countArrS++;
			break;
		case 'e':
			counterD = counterD + 1;
			if(counterD == 1){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 2){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 3){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 4){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 5){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 6){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 7){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}else if(counterS == 8){
				glBlendFunc(sFactor[counterS-1], dFactor[counterD-1]);
				glutPostRedisplay();
			}
			countArrD++;
			break;

			case '1':
				opacity = 0.00;
				opacityCount = 0;
				glutPostRedisplay();
				break;
			case '2':
				opacity = 0.25;
				opacityCount = 1;
				glutPostRedisplay();
				break;
			case '3':
				opacity = 0.50;
				opacityCount = 2;
				glutPostRedisplay();
				break;
			case '4':
				opacity = 0.75;
				opacityCount = 3;
				glutPostRedisplay();
				break;
			case '5':
				opacity = 1.00;
				opacityCount = 4;
				glutPostRedisplay();
				break;
		
			
			
	}

	
	

	if(countArrS >= 9){
		countArrS = 0;
	}
	if(counterS >=9){
		counterS = 0;
	}
	if(countArrD >= 8){
		countArrD = 0;
	}
	if(counterD >=8){
		counterD = 0;
	}
	if(opacity < 0){
		opacity = 0;
	}
	if(opacity >1){
		opacity = 1;
	}
	


	printf("[%d, %d]\n",counterS,counterD);
}

void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {
  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}


