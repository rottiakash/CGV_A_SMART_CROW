#include <GLUT/glut.h>
#include <iostream>
#include "bird.hpp"
#include "pot.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define SPACEBAR 32
#include "stb_image.h"
#define FLAP_DOWN -180
#define FLAP_UP 0
void drawtext(float, float, char *);
void menuS2(void);
unsigned int bg1, intro, bg2;

class State
{
public:
    static int flap;
    static int birdXpos;
    static int scene;
    static bool displayCloudS1;
    static bool moveBird;
    static bool water;
};
int State::flap = FLAP_DOWN;
int State::birdXpos = 0;
int State::scene = -1;
bool State::displayCloudS1 = false;
bool State::moveBird = false;
bool State::water = false;
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 0, 5000, 0, -500);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
}
void displayIntro(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, intro);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 10);
    glTexCoord2f(0, 0);
    glVertex3f(0, 5000, 10);
    glTexCoord2f(0, 1);
    glVertex3f(5000, 5000, 10);
    glTexCoord2f(1, 1);
    glVertex3f(5000, 0, 10);
    glTexCoord2f(1, 0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void displayScene1(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Bird bird;
    bird.drawBird(State::flap, State::birdXpos, 2000);
    glDisable(GL_TEXTURE_2D);
    if (State::displayCloudS1)
    {
        bird.cloud(3200, 2500, "Its a Sunny day", "I'm Thirsty");
        glColor3f(1, 1, 1);
        drawtext(2100, 430, "Press SPACEBAR to continue");
    }
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, bg1);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 10);
    glTexCoord2f(0, 0);
    glVertex3f(0, 5000, 10);
    glTexCoord2f(0, 1);
    glVertex3f(5000, 5000, 10);
    glTexCoord2f(1, 1);
    glVertex3f(5000, 0, 10);
    glTexCoord2f(1, 0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void displayScene2(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
    Pot pot;
    pot.draw(3500, 400, State::water);
    Bird bird;
    bird.drawBird(FLAP_DOWN, 3200, 1400);
    glFlush();
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, bg2);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 10);
    glTexCoord2f(0, 0);
    glVertex3f(0, 5000, 10);
    glTexCoord2f(0, 1);
    glVertex3f(5000, 5000, 10);
    glTexCoord2f(1, 1);
    glVertex3f(5000, 0, 10);
    glTexCoord2f(1, 0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void drawtext(float x, float y, char *s)
{
    glRasterPos2f(x, y);
    for (int i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
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
            State::displayCloudS1 = true;
            glFlush();
            glutIdleFunc(NULL);
        }
    }
}

void moveBird(void)
{
    if (State::scene == 0)
    {
        if (State::birdXpos <= 5000)
        {
            State::birdXpos += 50;
            glutPostRedisplay();
        }
        else
        {
            glutIdleFunc(NULL);
            State::scene = 1;
            glutDisplayFunc(displayScene2);
            glutPostRedisplay();
            menuS2();
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
void keyboard(unsigned char key, int x, int y)
{
    if (State::scene == -1)
    {
        if (key == 's' || key == 'S')
        {
            State::scene = 0;
            glutDisplayFunc(displayScene1);
            glutPostRedisplay();
        }
    }
    else if (State::scene == 0)
        if (State::displayCloudS1)
            if (key == SPACEBAR)
            {
                State::displayCloudS1 = false;
                glutIdleFunc(moveBird);
            }
}
void processMenuS2(int option)
{
    switch (option)
    {
    case 1:
        State::scene = -1;
        State::birdXpos = 0;
        glutDisplayFunc(displayIntro);
        glutPostRedisplay();
        break;
    case 2:
        if (State::water == false)
            State::water = true;
        else if (State::water == true)
            State::water = false;
        glutPostRedisplay();
        break;
    case 3:
        exit(0);
    }
}
void menuS2(void)
{

    int menu;

    // create the menu and
    // tell glut that "processMenuEvents" will
    // handle the events
    menu = glutCreateMenu(processMenuS2);

    //add entries to our menu
    glutAddMenuEntry("Reset", 1);
    glutAddMenuEntry("Toggle Water Level", 2);
    glutAddMenuEntry("Exit", 3);

    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void loadBackground(void)
{
    glGenTextures(1, &bg1);
    glBindTexture(GL_TEXTURE_2D, bg1);
    // set the bg1 wrapping/filtering options (on the currently bound bg1 object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the bg1
    int width, height, nrChannels;
    unsigned char *data = stbi_load("s1BG2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load bg1" << std::endl;
    }
    stbi_image_free(data);
}
void loadIntro(void)
{
    glGenTextures(1, &intro);
    glBindTexture(GL_TEXTURE_2D, intro);
    // set the bg1 wrapping/filtering options (on the currently bound bg1 object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the bg1
    int width, height, nrChannels;
    unsigned char *data = stbi_load("intro.psd", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load intro" << std::endl;
    }
    stbi_image_free(data);
}
void loadBackground2(void)
{
    glGenTextures(1, &bg2);
    glBindTexture(GL_TEXTURE_2D, bg2);
    // set the bg1 wrapping/filtering options (on the currently bound bg1 object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the bg1
    int width, height, nrChannels;
    unsigned char *data = stbi_load("s2BG.psd", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load bg1" << std::endl;
    }
    stbi_image_free(data);
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("A Smart Crow");
    glutDisplayFunc(displayIntro);
    glutMouseFunc(onClick);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    loadBackground();
    loadIntro();
    loadBackground2();
    init();
    glutMainLoop();
}