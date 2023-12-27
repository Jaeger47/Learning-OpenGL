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

/* Source code for "Camera & Events" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <gl/glut.h>
#include "stb_image.h"
#include <irr/irrKlang.h>
using namespace irrklang; //using namespace
using namespace std;

void display(); 
void reshape(int, int);
void update(int);
void cube();

void handleMouseMove(int, int);
void handleKeyPress(unsigned char, int, int);
void handleKeyRelease(unsigned char, int, int);
void updateCamera();

void loadTexture(const char*, GLuint&, GLenum);
void loadAllTextures();

int windowWidth = 800;
int windowHeight = 600;
int midWindowX;
int midWindowY;

ISoundEngine* engine = createIrrKlangDevice(); //declaring a sound device

bool keys[256]; // Array to keep track of pressed keys
bool mouseLocked = true;
float yaw = 0.0f;
float pitch = 0.0f;

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;
float moveSpeed = 0.5f;
float jumpSpeed = 0.2f;
float gravity = 0.010f;
bool isJumping = false;
bool isGrounded = true;

float _angle = -70.0f; // objects angle
GLuint grassTex;

//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; 
GLfloat mat_shininess[] = { 60.0 }; 


//set world light
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light[] = { 0.5, 0.5, 0.5 };
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

static GLint fogMode;
//Initializes 3D rendering
void initRendering() {

	engine->play2D("sound.wav", true); //playing 2d sund if true loop else false

	glClearColor(0.0,0.4,0.7,1.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	loadAllTextures();

	 glEnable(GL_FOG);
   {
      GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};

      fogMode = GL_EXP;
      glFogi (GL_FOG_MODE, fogMode);
      glFogfv (GL_FOG_COLOR, fogColor);
      glFogf (GL_FOG_DENSITY, 0.03);
      glHint (GL_FOG_HINT, GL_DONT_CARE);
      glFogf (GL_FOG_START, 1.0);
      glFogf (GL_FOG_END, 5.0);
   }
   glClearColor(0.5, 0.5, 0.5, 1.0);  /* fog color */

	
}



int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	
	//Create the window
	glutCreateWindow("Camera & Events - github.com/Jaeger47/Learning-OpenGL");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(handleMouseMove);
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease);
	glutTimerFunc(1000/60, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}

//Draws the 3D scene
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//camera controls
		gluLookAt(cameraX, cameraY, cameraZ, cameraX + sin(yaw), cameraY - pitch, cameraZ - cos(yaw), 0, 1, 0);


	//setting world lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light ); //add diffuse specular lighting
    glLightfv(GL_LIGHT0, GL_SPECULAR, light ); //add specular lighting
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess



	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);//add color material to object
	glTranslatef(3.0f, 0.0f, 0.0f); //location
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
	glutSolidTeapot (1.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glTranslatef(-3.0f, 0.0f, 0.0f); //location
	glRotatef(_angle, 1.0f, 0.0f, 0.0f); //rotation animation
	glutSolidTorus(0.5,1,24,48);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
	glTranslatef(0.0f, 3.0f, 0.0f); //location
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
	cube();
	glPopMatrix();


	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grassTex);


	glTranslatef(0.0f, -1.0f, 0.0f);
	glBegin(GL_QUADS);
		glColor3f(1.0f,1.0f,1.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0 , 0);
		glVertex3f(-1000.0f, -5.0f, -1000.0f);
			glTexCoord2f(1000, 0);
		glVertex3f(-1000.0f, -5.0f, 1000.0f);
			glTexCoord2f(1000.0f, 1000.0f);
		glVertex3f(1000.0f, -5.0f, 1000.0f);
			glTexCoord2f(0.0f, 1000.f);
		glVertex3f(1000.0f, -5.0f, -1000.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	
	

	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);

	windowWidth = w;
    windowHeight = h;
    midWindowX = w / 2;
    midWindowY = h / 2;
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}
	updateCamera();
	glutPostRedisplay();
	glutTimerFunc(1000/60, update, 0);
}
//keyboard controls
void handleMouseMove(int x, int y) {
    if (mouseLocked) {
        int deltaX = x - midWindowX;
        int deltaY = y - midWindowY;

        yaw += deltaX * 0.001f;
        pitch += deltaY * 0.001f;

        if (pitch > 1.5f) pitch = 1.5f;
        else if (pitch < -1.5f) pitch = -1.5f;

        glutWarpPointer(midWindowX, midWindowY);
    }
	glutPostRedisplay();
}

void handleKeyPress(unsigned char key, int x, int y) {
    if (key == ' ') {
        if (isGrounded) {
            isJumping = true;
            isGrounded = false;
        }
    }
    keys[key] = true;
	glutPostRedisplay();
}

void handleKeyRelease(unsigned char key, int x, int y) {
    keys[key] = false;
	glutPostRedisplay();
}

void updateCamera() {
    if (keys['w']) { // Move forward
        cameraX += sin(yaw) * moveSpeed;
        cameraZ -= cos(yaw) * moveSpeed;
    }
    if (keys['s']) { // Move backward
        cameraX -= sin(yaw) * moveSpeed;
        cameraZ += cos(yaw) * moveSpeed;
    }
    if (keys['a']) { // Strafe left
        cameraX += sin(yaw - 3.1415926535 / 2) * moveSpeed;
        cameraZ -= cos(yaw - 3.1415926535 / 2) * moveSpeed;
    }
    if (keys['d']) { // Strafe right
        cameraX += sin(yaw + 3.1415926535 / 2) * moveSpeed;
        cameraZ -= cos(yaw + 3.1415926535 / 2) * moveSpeed;
    }

    if (isJumping) {
        cameraY += jumpSpeed;
        jumpSpeed -= gravity;
        if (cameraY <= 0.0f) {
            cameraY = 0.0f;
            isJumping = false;
            isGrounded = true;
            jumpSpeed = 0.2f;
        }
    }
	glutPostRedisplay();
}





void loadTexture(const char* fileName, GLuint& textureID, GLenum format) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        // Handle error loading texture
        std::cerr << "Failed to load texture: " << fileName << std::endl;
    }
}

void loadAllTextures() {
    
    loadTexture("grass.bmp", grassTex, GL_RGB); // Change GL_RGB to GL_RGBA for blending if needed

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
