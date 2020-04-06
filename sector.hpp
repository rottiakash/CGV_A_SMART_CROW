#include <GLUT/glut.h>
#include <math.h>
#include <iostream>
class Sector
{
private:
    float color[3];

public:
    void setColor(float r, float g, float b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void draw(int r, int startAngle, int stopAngle, int depthIndex, int xpos, int ypos)
    {
        float x = 0;
        float y = 0;
        glPushMatrix();
        glTranslatef(xpos, ypos, 0);
        glColor3fv(color);
        x = r * cos((startAngle * 3.142) / 180);
        y = r * sin((startAngle * 3.142) / 180);
        glBegin(GL_LINES);
        glVertex3f(0, 0, depthIndex);
        glVertex3f(x, y, depthIndex);
        glEnd();
        glBegin(GL_POLYGON);
        for (float t = startAngle; t <= stopAngle; t += 0.001)
        {
            float angle = (t * 3.142) / 180;
            x = r * cos(angle);
            y = r * sin(angle);
            glVertex3f(x, y, depthIndex);
        }
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(x, y, depthIndex);
        glVertex3f(0, 0, depthIndex);
        glEnd();
        glPopMatrix();
    }
};