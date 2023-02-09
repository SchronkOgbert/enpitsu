//
// Created by weekendUM on 2/3/2023.
//

#include "Triangles.h"
#include "Screen.h"

namespace enpitsu
{
    void Triangles::draw()
    {
        shaderProgram->getVao()->Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
//        println("drawing");
    }
} // enpitsu