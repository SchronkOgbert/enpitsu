#ifndef ENPITSU_LITSHADERBASE_H
#define ENPITSU_LITSHADERBASE_H

#include "enpitsu/objects/Screen.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"

namespace enpitsu
{
    class LitShaderBase : public SolidColor
    {
        std::vector<GLfloat > normals;
        std::unique_ptr<VBO> normalsVBO{nullptr};
        Screen* screen;

        bool flatShading{true};
    protected:
        void Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                    const bool &isStatic) override;
    public:
        explicit LitShaderBase(const Vector4 &color = {255, 255, 255, 255}, bool flat = true);

        ~LitShaderBase() override;

        void calculateNormals(bool flat = true);

        [[nodiscard]] bool isFlatShading() const;

        void setFlatShading(bool flatShading);

        void setScreen(Screen *screen);
    };

} // enpitsu

#endif //ENPITSU_LITSHADERBASE_H
