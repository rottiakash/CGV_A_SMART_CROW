#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "stone.hpp"
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
char *line1 = "I cannot reach";
char *line2 = "the water";
Bird bird;
Pot pot;
Stone stone;
class State
{
public:
    static int flap;
    static int birdXpos;
    static int birdYpos;
    static int scene;
    static bool displayCloudS1;
    static bool displayCloudS2;
    static bool moveBird;
    static bool water;
    static bool yMove;
};
int State::flap = FLAP_DOWN;
int State::birdXpos = 0;
int State::birdYpos = 1400;
int State::scene = -1;
bool State::displayCloudS1 = false;
bool State::displayCloudS2 = true;
bool State::moveBird = false;
bool State::water = false;
bool State::yMove = false;
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 0, 5000, 0, -500);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
}
void changeCloud(int value)
{
    line1 = "Let me use";
    line2 = "Some Stones";
    glutPostRedisplay();
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
    pot.draw(3500, 400, State::water);
    if (State::displayCloudS2)
        bird.cloud(4000, 2000, line1, line2);
    if (!State::yMove)
        bird.drawBird(FLAP_DOWN, 3200, 1400, "Collapse");
    else if (State::yMove)
        bird.drawBird(State::flap, 3200, State::birdYpos);
    stone.draw(4000, 300);
    stone.draw(3700, 200);
    stone.draw(3900, 150);
    stone.draw(3500, 200);
    stone.draw(4300, 100);
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
    glDisable(GL_TEXTURE_2D);
    glutTimerFunc(2000, changeCloud, 0);
    glutSwapBuffers();
}
void drawtext(float x, float y, char *s)
{
    glRasterPos2f(x, y);
    for (int i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}
void idle()
{
    if (State::scene == 0)
    {
        if (State::birdXpos <= 2000)
        {
            State::birdXpos += 30;
            glutPostRedisplay();
        }
        else
        {
            State::displayCloudS1 = true;
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
            State::birdXpos += 30;
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
void birdUp(void)
{
    if (State::birdYpos <= 1300)
    {
        State::birdYpos += 30;
        glutPostRedisplay();
    }
    else
    {
        glutIdleFunc(NULL);
        State::yMove = false;
        glutPostRedisplay();
    }
}
void birdDown(void)
{
    if (State::birdYpos >= 10)
    {
        State::birdYpos -= 30;
        glutPostRedisplay();
    }
    else
    {
        glutIdleFunc(NULL);
        glutIdleFunc(birdUp);
    }
}
void onClick(int btn, int state, int x, int y)
{
    if (State::scene == 0)
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            glutIdleFunc(idle);
    }
    else if (State::scene == 1)
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            //if (x >= 698 && x <= 895 && y >= 750 && y <= 805)
            {
                State::yMove = true;
                State::displayCloudS2 = false;
                glutIdleFunc(birdDown);
                glutPostRedisplay();
            }
        }
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
        State::flap = FLAP_DOWN;
        State::birdXpos = 0;
        State::birdYpos = 1400;
        State::scene = -1;
        State::displayCloudS1 = false;
        State::displayCloudS2 = true;
        State::moveBird = false;
        State::water = false;
        State::yMove = false;
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
    unsigned char *data = stbi_load("INTRO.psd", &width, &height, &nrChannels, 0);
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
    glutInitWindowSize(1440, 800);
    glutCreateWindow("A Smart Crow");
    glutDisplayFunc(displayIntro);
    glutMouseFunc(onClick);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);
    glEnable(GL_DEPTH_TEST);
    loadBackground();
    loadIntro();
    loadBackground2();
    init();
    glutMainLoop();
}