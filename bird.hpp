#include <GLUT/glut.h>
#include "line.hpp"
#include "ellipse.hpp"
#include "sector.hpp"
#include "circle.hpp"
#include "triangle.hpp"
class Bird
{
private:
    void tail(void)
    {
        Line line;
        line.setColor(0.128, 0.128, 0.128);
        line.draw(200, 400, 0, 350, 1);
        line.draw(200, 400, 30, 300, 1);
        line.draw(200, 400, 50, 240, 1);
        line.draw(200, 400, 110, 245, 1);
    }
    void body(void)
    {
        Ellipse ellipse;
        ellipse.setColor(0.128, 0.128, 0.128);
        ellipse.draw(500, 400, 300, 200, 2);
    }
    void wing(int flapState)
    {
        Sector sector;
        glPushMatrix();
        glTranslatef(500, 400, 0);
        glRotatef(flapState, 0, 0, 1);
        sector.setColor(0, 0, 0);
        sector.draw(400, 55, 125, 1);
        glFlush();
        glPopMatrix();
    }
    void face(void)
    {
        Circle circle;
        circle.setColor(0.128, 0.128, 0.128);
        circle.draw(170, 900, 400, 2, false);
    }
    void eye(void)
    {
        Circle circle;
        circle.setColor(1, 1, 1);
        circle.draw(20, 1000, 400, 1, false);
    }
    void beak(void)
    {
        Triangle triangle;
        triangle.setColor(0, 0, 0);
        triangle.draw(1000, 300, 1000, 500, 1150, 400, 2);
    }

    void drawtext(float x, float y, char *s)
    {
        glColor3f(0, 0, 0);
        glRasterPos2f(x, y);
        for (int i = 0; s[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }

public:
    void drawBird(int flapState, int xpos, int ypos)
    {
        glPushMatrix();
        glTranslatef(xpos, ypos, 0);
        tail();
        body();
        wing(flapState);
        face();
        eye();
        beak();
        glFlush();
        glPopMatrix();
    }
    void cloud(int xpos, int ypos, char *line1, char *line2)
    {
        glPushMatrix();
        glTranslatef(xpos, ypos, 0);
        Circle circle;
        circle.setColor(1, 1, 1);
        circle.draw(80, 80, 80, 1, false);
        circle.draw(120, 270, 200, 1, false);
        Ellipse ellipse;
        ellipse.setColor(1, 1, 1);
        ellipse.draw(680, 400, 300, 200, 1);
        drawtext(520, 420, line1);
        drawtext(520, 330, line2);
        glFlush();
        glPopMatrix();
    }
};