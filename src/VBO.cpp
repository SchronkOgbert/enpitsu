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
    glBufferData(GL_ARRAY_BUFFER, size, vertices,
                 isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
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

void VBO::UpdateScale(const enpitsu::Vector3 &newScale, ShaderProgram *shader) const
{
    shader->Bind();
    GLint scaleX = glGetUniformLocation(shader->getId(), "scaleX");
    GLint scaleY = glGetUniformLocation(shader->getId(), "scaleY");
    glUniform1f(scaleX, newScale.x);
    glUniform1f(scaleY, newScale.y);
    GLfloat newValX;
    glGetUniformfv(shader->getId(), scaleX, &newValX);
    PLOGD << "New X val: " << newValX;
    shader->Unbind();
}
