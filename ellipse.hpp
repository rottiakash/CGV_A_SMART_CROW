#include <GLUT/glut.h>
class Ellipse
{
private:
    float color[3];
    int depthIndex;
    void setPixel(int x, int y)
    {
        glColor3fv(color);
        glBegin(GL_POINTS);
        glVertex3i(x, y, this->depthIndex);
        glEnd();
        glFlush();
    }

    int round(const float a) { return int(a + 0.5); }
    void ellipsePlotPoints(int xCentre, int yCentre, int x, int y)
    {
        setPixel(xCentre + x, yCentre + y);
        setPixel(xCentre - x, yCentre + y);
        setPixel(xCentre + x, yCentre - y);
        setPixel(xCentre - x, yCentre - y);
    }

public:
    void setColor(float r, float g, float b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void draw(int xCenter, int yCenter, int Rx, int Ry, int depthIndex)
    {
        this->depthIndex = depthIndex;
        int Rx2 = Rx * Rx;
        int Ry2 = Ry * Ry;
        int twoRx2 = 2 * Rx2;
        int twoRy2 = 2 * Ry2;
        int p;
        int x = 0;
        int y = Ry;
        int px = 0;
        int py = twoRx2 * y;
        ellipsePlotPoints(xCenter, yCenter, x, y);
        p = round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
        while (px < py)
        {
            x++;
            px += twoRy2;
            if (p < 0)
                p += Ry2 + px;
            else
            {
                y--;
                py -= twoRx2;
                p += Ry2 + px - py;
            }
            ellipsePlotPoints(xCenter, yCenter, x, y);
        }
        p = round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
        while (y > 0)
        {
            y--;
            py -= twoRx2;
            if (p > 0)
                p += Rx2 - py;
            else
            {
                x++;
                px += twoRy2;
                p += Rx2 = py + px;
            }
            ellipsePlotPoints(xCenter, yCenter, x, y);
        }
    }
};