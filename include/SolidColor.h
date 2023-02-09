//
// Created by weekendUM on 2/8/2023.
//

#ifndef LIBTEST_SOLIDCOLOR_H
#define LIBTEST_SOLIDCOLOR_H

#include "ShaderProgram.h"
#include "GeometryEssentials.h"

namespace enpitsu
{

    class SolidColor : public ShaderProgram
    {
    protected:
        Vector4 color;
        std::vector<GLfloat > colorInfo;
        std::unique_ptr<VBO> colorVertex;
    public:
        explicit SolidColor(const Vector4& rgbaColor);

        void Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                    const bool &isStatic) override;
    };

} // enpitsu

#endif //LIBTEST_SOLIDCOLOR_H
