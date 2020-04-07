#include <GLUT/glut.h>
#include "circle.hpp"
#include "line.hpp"
#include "ellipse.hpp"
#include "sector.hpp"
#include "Triangle.hpp"
#define FLAP_DOWN -180
#define FLAP_UP 0
class State
{
public:
    static int flap;
};
int State::flap = FLAP_DOWN;
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
    /*         Circle circle;
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
    sector.drawWing(State::flap, 1, 2000, 2000); */
    Triangle triangle;
    triangle.setColor(0, 0, 0);
    triangle.draw(1000, 1000, 3000, 1000, 2000, 3000, 1);
    glFlush();
    glutSwapBuffers();
}
void timer(int value)
{
    if (State::flap == FLAP_DOWN)
        State::flap = FLAP_UP;
    else if (State::flap == FLAP_UP)
        State::flap = FLAP_DOWN;
    glutTimerFunc(500, timer, 0);
    glutPostRedisplay();
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("A Smart Crow");
    glutDisplayFunc(displayScene1);
    glutTimerFunc(1000, timer, 0);
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
}