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

/* Source code for "Hello window" by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */
//Mark Daniel G. Dacer
//github.com/Jaeger47/Learning-OpenGL

#include <iostream>
#include <glut.h>

using namespace std;


void display(); //declare a function prototype

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //sets diplay to rgb

	glutInitWindowPosition(200,100); //position of the program in your screen
	glutInitWindowSize(500,500); //size of the program window

   	glutCreateWindow("Hello Window - github.com/Jaeger47/Learning-OpenGL"); //window title
	glutDisplayFunc(display);//call display function
	glutMainLoop(); //loop all functions
	
	
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//Indicates the buffers currently enabled for color writing.
	glLoadIdentity();//reset all matrix
	glutSwapBuffers(); //Send the scene to the screen
}
