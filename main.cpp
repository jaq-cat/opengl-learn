#include <iostream>
#include <GL/glut.h>

void display() {
    glClearColor(0.1, 0.0, 0.1, 1.0); // dark purple background
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();

    glFlush(); // render
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL!");
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
