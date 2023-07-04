#include "enpitsu/objects/Triangles3D.h"
#include "enpitsu/GL/Wrapper.h"

namespace enpitsu
{
    void Triangles3D::draw()
    {
        Object3D::draw();
#ifdef DEBUG
        callGLFunction(glDrawElements, GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
#else
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
#endif
    }
} // enpitsu