#include "objects/Triangles3D.h"

namespace enpitsu
{
    void Triangles3D::draw()
    {
        Object3D::draw();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
    }
} // enpitsu