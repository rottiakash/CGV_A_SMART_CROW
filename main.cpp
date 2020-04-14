#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "stone.hpp"
#include <fstream>
#include <string>
#include "bird.hpp"
#include "pot.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define SPACEBAR 32
#include "stb_image.h"
#define FLAP_DOWN -180
#define FLAP_UP 0
void drawtext(float, float, char *);
std::string getFileContents(std::ifstream &);
void menuS2(void);
unsigned int bg1, intro, bg2, moral;
char *line1 = "I cannot reach";
char *line2 = "the water";
char *line3 = "";
char *line4 = "";
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
    static int stones;
    static bool mouthStone;
    static char *line;
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
bool State::mouthStone = false;
int State::stones = 0;
char *State::line = "Click to continue";
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 0, 5000, 0, -500);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
}
void doExit(void)
{
    std::ifstream Reader("ART.txt"); //Open file

    std::string Art = getFileContents(Reader); //Get file

    std::cout << Art << std::endl; //Print it to the screen

    Reader.close(); //Close file

    exit(0);
}
void changeCloud(int value)
{
    if (State::stones == 0)
    {
        line1 = "Let me use";
        line2 = "Some Stones";
        line3 = "Use Right Click Menu to toggle Water Level";
        line4 = "Click the Stone to drop it in Pot";
        glutPostRedisplay();
    }
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
    }
    glColor3f(1, 1, 1);
    drawtext(2100, 430, State::line);
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
    pot.draw(3500, 400, State::water, State::stones, stone);
    if (State::displayCloudS2)
        bird.cloud(4000, 2000, line1, line2);
    if (!State::yMove)
        bird.drawBird(FLAP_DOWN, 3200, 1400, "Collapse");
    else if (State::yMove)
        bird.drawBird(State::flap, 3200, State::birdYpos);
    if (State::mouthStone)
        stone.draw(4350, 380 + State::birdYpos);
    stone.draw(4000, 300);
    stone.draw(4200, 200);
    stone.draw(3900, 150);
    stone.draw(4300, 200);
    stone.draw(4500, 100);
    glColor3f(0, 0, 0);
    drawtext(1800, 4800, line3);
    drawtext(2000, 4600, line4);
    drawtext(2100, 430, State::line);
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
    glutTimerFunc(3000, changeCloud, 0);
    glutSwapBuffers();
}
void displayMoral(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, moral);
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
            State::birdXpos += 30;
            glutPostRedisplay();
        }
        else
        {
            State::line = "Press SPACEBAR to continue";
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
            State::line = "";
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
        State::mouthStone = false;
        if (State::stones < 3)
        {
            State::stones++;
            line1 = "I Need more";
            line2 = "Stones";
        }
        if (State::stones == 3)
        {
            line1 = "I can now";
            line2 = "Drink Water";
            State::line = "Press SPACEBAR to continue";
        }

        State::displayCloudS2 = true;
        glutPostRedisplay();
    }
}
void birdDown(void)
{
    if (State::birdYpos >= 10 && State::stones < 3)
    {
        State::birdYpos -= 30;
        glutPostRedisplay();
    }
    else
    {
        State::mouthStone = true;
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
    {
        if (State::displayCloudS1)
        {
            if (key == SPACEBAR)
            {
                State::displayCloudS1 = false;
                glutIdleFunc(moveBird);
            }
        }
    }
    else if (State::scene == 1)
    {
        if (line1 == "I can now")
        {
            if (key == SPACEBAR)
            {
                State::scene = 2;
                glutDisplayFunc(displayMoral);
                glutPostRedisplay();
            }
        }
    }
    else if (State::scene == 2)
    {

        if (key == 27)
        {
            doExit();
        }
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
        State::mouthStone = false;
        State::stones = 0;
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
        doExit();
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
    if (State::scene == 1)
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
void loadMoral(void)
{
    glGenTextures(1, &moral);
    glBindTexture(GL_TEXTURE_2D, moral);
    // set the bg1 wrapping/filtering options (on the currently bound bg1 object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the bg1
    int width, height, nrChannels;
    unsigned char *data = stbi_load("MORAL.psd", &width, &height, &nrChannels, 0);
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
    glutCreateWindow("A Smart Crow");
    glutFullScreen();
    glutDisplayFunc(displayIntro);
    glutMouseFunc(onClick);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);
    glEnable(GL_DEPTH_TEST);
    loadBackground();
    loadIntro();
    loadBackground2();
    loadMoral();
    init();
    menuS2();
    glutMainLoop();
}

std::string getFileContents(std::ifstream &File)
{
    std::string Lines = ""; //All lines

    if (File) //Check if everything is good
    {
        while (File.good())
        {
            std::string TempLine;         //Temp line
            std::getline(File, TempLine); //Get temp line
            TempLine += "\n";             //Add newline character

            Lines += TempLine; //Add newline
        }
        return Lines;
    }
    else //Return error
    {
        return "ERROR File does not exist.";
    }
}