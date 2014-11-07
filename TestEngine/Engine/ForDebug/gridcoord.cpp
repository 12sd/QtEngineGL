#include "gridcoord.h"

GridCoord::GridCoord()
{
    r = g = b = 1.0f;
}

void GridCoord::SetColor(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

//Вызывать последним, выполнив все UnBind()
void GridCoord::Draw(float left, float right, float bottom, float top, float step)
{
    ///* Заменить
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //*/

    for (int i = left; i < right; i+=step)
    {
        ///* Веременный рендер
        glBegin(GL_LINES);
        glColor3f(r, g, b);
        glVertex3f(left, i, 0.1f);
        glColor3f(r, g, b);
        glVertex3f(right, i, 0.1f);
        glEnd();
        //*/
    }

    for (int i = bottom; i < top; i+=step)
    {
        ///* Веременный рендер
        glBegin(GL_LINES);
        glColor3f(r, g, b);
        glVertex3f(i, bottom, 0.1f);
        glColor3f(r, g, b);
        glVertex3f(i, top, 0.1f);
        glEnd();
        //*/
    }

    /* Не рабочий вариант
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &buf_ver[0]);
    //glDrawArrays(GL_LINES, 0, (count_x + count_y) * 2);
    glDrawArrays(GL_LINES, 8, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
    */
}
