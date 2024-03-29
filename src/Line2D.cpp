#include "enpitsu/objects/Line2D.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/objects/Screen.h"

enpitsu::Line2D::Line2D(enpitsu::Screen *screen, const std::vector<Vector2> &points, const bool &isStatic) :
        Object2D(screen, points, Vector2(0, 0), newShader<SolidColor>(Vector4(64.0f, 64.0f, 64.0f, 128), "default.vert",
                                                               "default.frag"),
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
