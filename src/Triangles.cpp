//
// Created by weekendUM on 2/3/2023.
//

#include "Triangles.h"
#include "Screen.h"

namespace enpitsu
{
    void Triangles::draw()
    {
        Object2D::draw();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
//        println("drawing");
    }
} // enpitsu