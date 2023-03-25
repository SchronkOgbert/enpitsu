//
// Created by weekendUM on 2/3/2023.
//

#include "objects/Triangles2D.h"
#include "objects/Screen.h"

namespace enpitsu
{
    void Triangles2D::draw()
    {
        Object2D::draw();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
    }
} // enpitsu