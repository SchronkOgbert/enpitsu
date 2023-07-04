#include "enpitsu/GL/VBO.h"
#include "enpitsu/GL/Wrapper.h"
#include "enpitsu/shading/ShaderProgram.h"

using namespace enpitsu;

GLuint VBO::getId() const
{
    return ID;
}

VBO::VBO(GLfloat *vertices, const GLsizeiptr &size, const VBO::objectLayout &layout, const bool &isStatic) :
        layout(layout), size(size)
{
    callGLFunction(glGenBuffers, 1, &ID);
    callGLFunction(glBindBuffer, GL_ARRAY_BUFFER, ID);
    callGLFunction(glBufferData, GL_ARRAY_BUFFER, size, vertices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void VBO::Bind() const
{
#ifdef DEBUG
    callGLFunction(glBindBuffer, GL_ARRAY_BUFFER, ID);
#else
    glBindBuffer(GL_ARRAY_BUFFER, ID);
#endif
}

void VBO::Unbind() const
{
#ifdef DEBUG
    callGLFunction(glBindBuffer, GL_ARRAY_BUFFER, static_cast<GLuint>(0));
#else
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(0));
#endif
}

void VBO::Delete()
{
    callGLFunction(glDeleteBuffers, 1, &ID);
}

void VBO::Update(GLfloat *newVertices) const
{
    this->Bind();
    callGLFunction(glBufferSubData, GL_ARRAY_BUFFER, 0, size, newVertices);
    this->Unbind();
}

unsigned int VBO::getSize() const
{
    return size;
}

void VBO::setSize(unsigned int size)
{
    VBO::size = size;
}

VBO::~VBO() = default;
