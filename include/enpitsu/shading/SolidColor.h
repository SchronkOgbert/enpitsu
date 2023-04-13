#ifndef ENPITSU_SOLIDCOLOR_H
#define ENPITSU_SOLIDCOLOR_H

#include "ShaderProgram.h"
#include "enpitsu/helpers/GeometryEssentials.h"

namespace enpitsu
{

    class SolidColor : public ShaderProgram
    {
    protected:
        Vector4 color;
        std::vector<GLfloat > colorInfo;
        std::unique_ptr<VBO> colorVertex;
    public:
        explicit SolidColor(const Vector4 &rgbaColor,
                            const char *vertexFile = "default.vert",
                            const char *fragmentFile = "default.frag");

        void Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                    const bool &isStatic) override;
    };

} // enpitsu

#endif //ENPITSU_SOLIDCOLOR_H
