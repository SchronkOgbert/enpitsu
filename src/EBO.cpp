#include "enpitsu/GL/EBO.h"
#include "enpitsu/GL/Wrapper.h"

using namespace enpitsu;

GLuint EBO::getId() const
{
    return ID;
}

EBO::EBO(GLuint *indices, const GLsizeiptr &size, const bool &isStatic)
{
    callGLFunction(glGenBuffers, 1, &ID);
    callGLFunction(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ID);
    callGLFunction(glBufferData, GL_ELEMENT_ARRAY_BUFFER, size, indices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void EBO::Bind() const
{
#ifdef DEBUG
    callGLFunction(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ID);
#else
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
#endif
}

void EBO::Unbind() const
{
#ifdef DEBUG
    callGLFunction(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(0));
#else
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(0));
#endif
}

void EBO::Delete()
{
    callGLFunction(glDeleteBuffers, 1, &ID);
}

GLsizeiptr EBO::getSize() const
{
    return size;
}

void EBO::setSize(GLsizeiptr size)
{
    EBO::size = size;
}

void EBO::Update(GLuint *indices) const
{
    this->Bind();
    callGLFunction(glBufferSubData, GL_ELEMENT_ARRAY_BUFFER, 0, size, indices);
}

EBO::~EBO() = default;
