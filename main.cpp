#include <GL/glut.h>
#include "bird.hpp"
#define FLAP_DOWN -180
#define FLAP_UP 0
class State
{
public:
    static int flap;
    static int birdXpos;
    static int scene;
};
int State::flap = FLAP_DOWN;
int State::birdXpos = 0;
int State::scene = 0;
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
    bird.drawBird(State::flap, State::birdXpos, 2000);
    glFlush();
    glutSwapBuffers();
}
void idle()
{
    if (State::scene == 0)
    {
        if (State::birdXpos <= 2000)
        {
            State::birdXpos += 50;
            glutPostRedisplay();
        }
        else
        {
            glutIdleFunc(NULL);
        }
    }
}
void onClick(int btn, int state, int x, int y)
{
    if (State::scene == 0)
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            glutIdleFunc(idle);
    }
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
    glutMouseFunc(onClick);
    glutTimerFunc(1000, timer, 0);
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
}