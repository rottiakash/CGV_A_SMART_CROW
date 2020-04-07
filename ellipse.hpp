#include <GLUT/glut.h>
#include <math.h>
class Ellipse
{
private:
    float color[3];
    int depthIndex;

public:
    void setColor(float r, float g, float b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void draw(int xCenter, int yCenter, int Rx, int Ry, int depthIndex)
    {
        glPushMatrix();
        glTranslatef(xCenter, yCenter, 0);
        glColor3fv(color);
        glBegin(GL_POLYGON);
        for (float i = 0; i <= 360; i += 0.001)
        {
            float x = Rx * cos((i * 3.142) / 180);
            float y = Ry * sin((i * 3.142) / 180);
            glVertex3f(x, y, depthIndex);
        }
        glEnd();
        glFlush();
        glPopMatrix();
    }
};