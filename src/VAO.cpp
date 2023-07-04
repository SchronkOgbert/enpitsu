#include "enpitsu/GL/VAO.h"
#include "enpitsu/GL/VBO.h"
#include "enpitsu/GL/Wrapper.h"

using namespace enpitsu;

GLuint VAO::getId() const
{
    return ID;
}

VAO::VAO(const GLint &vertexSize) : vertexSize(vertexSize)
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO vbo)
{
    vbo.Bind();
    auto layout = vbo.getLayout();
    switch (vbo.getLayout())
    {
        case VBO::objectLayout::VERTEX2D:
        case VBO::objectLayout::TEXTURE2D: // these are both vec2, so we only need 1 branch for both
            callGLFunction(glVertexAttribPointer, static_cast<GLuint>(layout), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::VERTEX3D:
        case VBO::objectLayout::NORMAL: // these are both vec3, so we only need 1 branch for both
            callGLFunction(glVertexAttribPointer, static_cast<GLuint>(layout), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::RGBA:
            callGLFunction(glVertexAttribPointer, static_cast<GLuint>(layout), 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
    }
    callGLFunction(glEnableVertexAttribArray, static_cast<GLuint>(layout));
    vbo.Unbind();
}

void VAO::Bind() const
{
#ifdef DEBUG
    callGLFunction(glBindVertexArray, ID);
#else
    glBindVertexArray(ID);
#endif
}

void VAO::Unbind() const
{
#ifdef DEBUG
    callGLFunction(glBindVertexArray, 0);
#else
    glBindVertexArray(0);
#endif
}

void VAO::Delete()
{
    callGLFunction(glDeleteVertexArrays, 1, &ID);
}

VAO::~VAO() = default;
