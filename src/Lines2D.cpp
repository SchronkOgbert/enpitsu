#include "enpitsu/objects/Lines2D.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{
    Lines2D::Lines2D(Screen *screen, const std::vector<Vector2> &points, std::shared_ptr<ShaderProgram> &&shader, const bool &isStatic):
            Object2D(screen, points, Vector2(0, 0), std::forward<std::shared_ptr<ShaderProgram>>(shader), isStatic)
    {
        if(points.size() < 2)
        {
            throw BadLines2DException();
        }
        indices.resize(points.size() + 1);
        for(auto i = 0; i < points.size(); i++)
        {
            indices[i] = i;
        }
        indices[points.size()] = 0;
    }

    void Lines2D::draw()
    {
        Object2D::draw();
        glDrawArrays(GL_LINES, 0, indices.size());
    }
} // enpitsu