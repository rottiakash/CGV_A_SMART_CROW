#include <GLUT/glut.h>
#include "circle.hpp"
#include "line.hpp"
#include "ellipse.hpp"
#include "sector.hpp"
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 0, 5000, 0, -500);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
}

void displayScene1(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Circle circle;
    circle.setColor(0, 0, 0);
    circle.draw(500, 2000, 1000, 1);
    Line line;
    line.setColor(0, 0, 0);
    line.draw(1000, 1000, 2000, 2000, 1);
    Ellipse ellipse;
    ellipse.setColor(0, 0, 0);
    ellipse.draw(1000, 1000, 1000, 500, 1);
    Sector sector;
    sector.setColor(0, 0, 0);
    sector.draw(500, 0, 360, 1, 1000, 1000);
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("A Smart Crow");
    glutDisplayFunc(displayScene1);
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
}