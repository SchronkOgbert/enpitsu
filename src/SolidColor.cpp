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
        ShaderProgram::Create(vertices, indices, vertexSize, isStatic);
        colorInfo.resize(vertices.size() / vertexSize * 4);
        for (auto i = 0; i < colorInfo.size(); i++)
        {
            colorInfo[i++] = static_cast<float>(color.x) / 255.0f;
            colorInfo[i++] = static_cast<float>(color.y) / 255.0f;
            colorInfo[i++] = static_cast<float>(color.z) / 255.0f;
            colorInfo[i] = static_cast<float>(color.a) / 255.0f;
        }
        std::cout << "size of color info: " << sizeof(GLfloat) * colorInfo.size() << '\n';
//        for (auto &vertex: colorInfo)
//        {
//            std::cout << "color vertex: " << vertex << '\n';
//        }
        colorVertex = std::make_unique<VBO>(&colorInfo[0U],
                                            sizeof(GLfloat) * colorInfo.size(), VBO::objectLayout::RGBA,
                                            isStatic);
        vao->LinkVBO(*colorVertex);
        colorVertex->Unbind();
    }
} // enpitsu