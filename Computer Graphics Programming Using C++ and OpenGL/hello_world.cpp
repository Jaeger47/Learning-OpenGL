// hello_window.cpp
//
// created by Mark Daniel G. Dacer at BukSU
// https://jaeger47.github.io/Learning-OpenGL/
//

#include <GL/glut.h> // OpenGL Utility 

void display();

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB); //sets diplay to rgb
	glutInitWindowPosition(200,100); //position of the program in your screen
	glutInitWindowSize(500,500); //size of the program window
    	glutCreateWindow("Hello Window"); //window title
	glutDisplayFunc(display);//call display function

	glutMainLoop(); //loop all functions
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT); //Indicates the buffers currently enabled for color writing.
	glLoadIdentity();//reset all matrix
}
