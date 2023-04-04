//
// Created by weekendUM on 2/8/2023.
//

#include "enpitsu/shading/SolidColor.h"

namespace enpitsu
{
    SolidColor::SolidColor(const Vector4 &rgbaColor, const char *vertexFile, const char *fragmentFile) :
            ShaderProgram(vertexFile, fragmentFile), color(rgbaColor)
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
        PLOGD << "size of color info: " << sizeof(GLfloat) * colorInfo.size();
        colorVertex = std::make_unique<VBO>(&colorInfo[0U],
                                            sizeof(GLfloat) * colorInfo.size(), VBO::objectLayout::RGBA,
                                            isStatic);
        vao->LinkVBO(*colorVertex);
        colorVertex->Unbind();
    }
} // enpitsu