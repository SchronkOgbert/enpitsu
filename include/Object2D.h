//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_OBJECT2D_H
#define LIBTEST_OBJECT2D_H

#include "Object.h"
#include "GeometryEssentials.h"
#include "VAO.h"
#include "EBO.h"
#include "SolidColor.h"
#include "Exception.h"
#include <memory>
#include <vector>

namespace enpitsu
{
    class BadShaderObject : public Exception
    {
    public:
        BadShaderObject() : Exception("The shader cannot be NULL pointer")
        {}
    };

    class Object2D : public Object
    {
        Vector2 origin{};
    protected:

        std::vector<GLfloat > vertices;
        std::vector<GLuint > indices;
        std::unique_ptr<ShaderProgram> shaderProgram;
        bool scaleToScreen = false;
    public:
        using Object::Object;

        [[nodiscard]] bool isScaleToScreen() const;

        void setScaleToScreen(const bool &scaleToScreen);

        [[nodiscard]] const Vector2 &getOrigin() const;
        void setOrigin(const Vector2 &origin);

        explicit Object2D(Screen *screen, const std::vector<Vector2> &points,
                          ShaderProgram *shader = new SolidColor(Vector4(0.8f, 0.3f, 0.02f, 1.0f)),
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