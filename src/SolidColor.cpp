//
// Created by weekendUM on 2/8/2023.
//

#include "SolidColor.h"
#include "iostream"

namespace enpitsu
{
    SolidColor::SolidColor(const Vector4 &rgbaColor) :
    ShaderProgram("shaders/default.vert", "shaders/default.frag"), color(rgbaColor)
    {

    }

    void
    SolidColor::Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                       const bool &isStatic)
    {
        colorInfo.resize(vertices.size() / vertexSize * 4);
        for(auto i = 0; i < colorInfo.size(); i++)
        {
            colorInfo[i++] = static_cast<float>(color.x);
            colorInfo[i++] = static_cast<float>(color.y);
            colorInfo[i++] = static_cast<float>(color.z);
            colorInfo[i] = static_cast<float>(color.a);
        }
        std::cout << "size of color info: " << sizeof(GLfloat) * colorInfo.size() << '\n';
        for(auto & vertex: colorInfo)
        {
            std::cout << "color vertex: " << vertex << '\n';
        }
        colorVertex = std::make_unique<VBO>(&colorInfo[0U],
                                            sizeof(GLfloat) * colorInfo.size(), isStatic);
        ShaderProgram::Create(vertices, indices, vertexSize, isStatic);
        vao->LinkVBO(*colorVertex, 1U);
    }
} // enpitsu