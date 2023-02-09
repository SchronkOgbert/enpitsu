//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_OBJECT2D_H
#define LIBTEST_OBJECT2D_H

#include "Object.h"
#include "GeometryEssentials.h"
#include "VAO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include <memory>
#include <vector>

namespace enpitsu
{
    class Object2D : public Object
    {
        Vector2 origin{};
    protected:

        std::vector<GLfloat > vertices;
        std::vector<GLuint > indices;
        std::vector<GLfloat > colorValues{0.5f, 0.0f, 0.0f, 1.0f};
        std::unique_ptr<VAO> vao;
        std::unique_ptr<VBO> vertexPosition;
        std::unique_ptr<VBO> color;
        std::unique_ptr<EBO> ebo;
        std::unique_ptr<ShaderProgram> shaderProgram;
        bool scaleToScreen = false;
    public:
        [[nodiscard]] bool isScaleToScreen() const;
        void setScaleToScreen(const bool &scaleToScreen);

        [[nodiscard]] const Vector2 &getOrigin() const;

        void setOrigin(const Vector2 &origin);
        using Object::Object;

        explicit Object2D(Screen *screen, const std::vector<Vector2> &points,
                 const bool &isStatic = true,
                 const std::vector<unsigned int> &drawOrder = std::vector<unsigned int>(0U));

        void init() override;

        void onDestroy() override;

    protected:
        void draw() override;

    protected:
    };
}


#endif //LIBTEST_OBJECT2D_H
