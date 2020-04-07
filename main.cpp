#include <GLUT/glut.h>
#include "bird.hpp"
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
    Bird bird;
    bird.drawBird(State::flap, 2000, 2000);
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