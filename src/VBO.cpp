#include "enpitsu/GL/VBO.h"
#include "enpitsu/shading/ShaderProgram.h"

using namespace enpitsu;
GLuint VBO::getId() const
{
    return ID;
}

VBO::VBO(GLfloat *vertices, const GLsizeiptr &size, const VBO::objectLayout &layout, const bool &isStatic) :
        layout(layout), size(size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(0));
}

void VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

void VBO::Update(GLfloat *newVertices) const
{
    this->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, newVertices);
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

VBO::~VBO()
{

}
