#include <GLUT/glut.h>
#include <iostream>
#include "bird.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define FLAP_DOWN -180
#define FLAP_UP 0
unsigned int texture;
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
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(0, 800, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1500, 800, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1500, 0, 1);
    glTexCoord2f(1, 0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
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

void loadTexture(void)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("cloud.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
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
    glEnable(GL_TEXTURE_2D);
    loadTexture();
    init();
    glutMainLoop();
}