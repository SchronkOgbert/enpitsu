#include "enpitsu/objects/Triangles2D.h"
#include "enpitsu/objects/Screen.h"

namespace enpitsu
{
    void Triangles2D::draw()
    {
        Object2D::draw();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
    }
} // enpitsu