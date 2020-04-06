#include <GLUT/glut.h>
class Circle
{
private:
    int depthIndex;
    float color[3];
    void drawPixel(int x, int y)
    {
        glBegin(GL_POINTS);
        glVertex3i(x, y, this->depthIndex);
        glEnd();
        glFlush();
    }

    void symmetry(int x, int y)
    {
        drawPixel(x, y);
        drawPixel(y, x);
        drawPixel(-x, y);
        drawPixel(-y, x);
        drawPixel(x, -y);
        drawPixel(-y, -x);
        drawPixel(y, -x);
        drawPixel(-x, -y);
    }

public:
    void setColor(float r, float g, float b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void draw(int r, float xpos, float ypos, int depthIndex)
    {
        this->depthIndex = depthIndex;
        glPushMatrix();
        glTranslatef(xpos, ypos, 0);
        int d, x, y;
        x = 0;
        y = r;
        d = 1 - r;
        glColor3fv(color);
        symmetry(x, y);
        while (x <= y)
        {
            if (d < 0)
                d += 2 * x + 3;
            else
            {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
            symmetry(x, y);
        }
        glFlush();
        glPopMatrix();
    }
};