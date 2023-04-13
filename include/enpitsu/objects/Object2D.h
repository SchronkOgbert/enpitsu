#ifndef ENPITSU_OBJECT2D_H
#define ENPITSU_OBJECT2D_H

#include "enpitsu/helpers/defines.h"

#include "Object.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/GL/VAO.h"
#include "enpitsu/GL/EBO.h"
#include "enpitsu/shading/SolidColor.h"
#include "enpitsu/helpers/Exception.h"

namespace enpitsu
{
    class BadShaderObject : public Exception
    {
    public:
        BadShaderObject() : Exception("The shader cannot be NULL pointer")
        {}
    };
    class BadObjectSize : public Exception
    {
    public:
        BadObjectSize() : Exception("The size of the object should be greater than Vector2(0, 0)") {}
    };

    class Object2D : public Object
    {
        Vector2 origin{};
        Vector2 size{1, 1};
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
                          ShaderProgram *shader = new SolidColor(Vector4(0.8f, 0.3f, 0.02f, 1.0f), "default.vert",
                                                                 "default.frag"),
                          const bool &isStatic = true,
                          const std::vector<unsigned int> &drawOrder = std::vector<unsigned int>(0U));

        void init() override;

    protected:
        void tick(const float &delta) override;

    public:

        void onDestroy() override;

        /**
         * Sets location in absolute screen coordinates
         * @param newLocation new screen coords
         */
        void setLocation(const Vector2& newLocation);

        [[nodiscard]] Vector2 getLocation() const { return this->origin; }

        /**
         * The default size is (1.0, 1.0). This new size should also be in percentages
         * @param newSize
         */
        void setSize(const Vector2& newSize);

    protected:
        void draw() override;
    };
}


#endif //ENPITSU_OBJECT2D_H
