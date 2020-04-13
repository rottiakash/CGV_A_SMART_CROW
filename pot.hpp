#ifndef POT_H
#define POT_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "ellipse.hpp"

class Pot
{
public:
    void draw(int xpos, int ypos, bool hollow)
    {
        int lw;
        if (hollow)
            lw = 5;
        else
            lw = 2;
        glPushMatrix();
        glTranslatef(xpos, ypos, 0);
        glLineWidth(lw);
        Ellipse ellipse;
        ellipse.setColor(0, 0, 0);
        ellipse.draw(400, 300, 400, 300, 9, true, 117, 360, lw);
        ellipse.draw(400, 300, 400, 300, 9, true, 0, 60, lw);
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex3f(220, 560, 8);
        glVertex3f(270, 900, 8);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(600, 560, 8);
        glVertex3f(540, 900, 8);
        glEnd();
        ellipse.draw(400, 980, 250, 100, 7, true, 0, 360, lw);
        ellipse.draw(400, 980, 200, 50, 7, true, 0, 360, lw);
        glPopMatrix();
        if (!hollow)
        {
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
            glTranslatef(xpos, ypos, 0);
            glLineWidth(lw);
            Ellipse ellipse;
            ellipse.setColor(0.43, 0.32, 0.24);
            ellipse.draw(400, 300, 400, 300, 9, false, 0, 360, lw);
            glColor3f(0.43, 0.32, 0.24);
            glBegin(GL_POLYGON);
            glVertex3f(220, 560, 8);
            glVertex3f(600, 560, 8);
            glVertex3f(540, 900, 8);
            glVertex3f(270, 900, 8);
            glEnd();
            ellipse.draw(400, 980, 250, 100, 8, false, 0, 360, lw);
            ellipse.setColor(0, 0, 0);
            ellipse.draw(400, 980, 200, 50, 7, false, 0, 360, lw);
            glPopMatrix();
        }
    }
};

#endif /* POT_H */