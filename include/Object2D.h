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
        bool isStatic;

        void forceSetLocation(const Vector2& newLocation) noexcept;
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

        explicit Object2D(Screen *screen, const std::vector<Vector2> &points, const Vector2 &origin,
                          ShaderProgram *shader = new SolidColor(Vector4(0.8f, 0.3f, 0.02f, 1.0f)),
                          const bool &isStatic = true,
                          const std::vector<unsigned int> &drawOrder = std::vector<unsigned int>(0U));

        void init() override;

    protected:
        void tick(const float &delta) override;

    public:

        void onDestroy() override;

        void setLocation(const Vector2& newLocation);

        virtual void resize() = 0;

    protected:
        void draw() override;
    };
}


#endif //LIBTEST_OBJECT2D_H
