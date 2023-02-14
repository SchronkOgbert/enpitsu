//
// Created by weekendUM on 2/3/2023.
//

#include "Line2D.h"
#include "Screen.h"

enpitsu::Line2D::Line2D(enpitsu::Screen *screen, const std::vector<Vector2> &points, const bool &isStatic) :
        Object2D(screen, points, Vector2(0, 0), new SolidColor(Vector4(128.0f, 0.0f, 0.0f, 255)),
                 isStatic, {0, 1, 0})
{
    if(points.size() != 2)
    {
        throw BadLine2DException();
    }
}

void enpitsu::Line2D::draw()
{
    Object2D::draw();
    glDrawArrays(GL_LINES, 0, 2);
}
