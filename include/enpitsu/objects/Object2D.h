#ifndef ENPITSU_OBJECT2D_H
#define ENPITSU_OBJECT2D_H

#include "enpitsu/helpers/Drawable.h"
#include "enpitsu/helpers/defines.h"

#include "Object.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/GL/VAO.h"
#include "enpitsu/GL/EBO.h"
#include "enpitsu/shading/ShaderProgram.h"
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

    class Object2D : public Object, public Drawable
    {
        void forceSetLocation(const Vector2& newLocation) noexcept;

        void forceSetScale(const Vector2& newScale);

        void forceSetRotation(const float& rotation);
    protected:
        Vector2 origin{};
        Vector2 size{1, 1};
        float rotation{0};
        bool isStatic;

        glm::mat4 model{1};
        bool updateModel = false;

        std::vector<GLfloat > vertices;
        std::vector<GLuint > indices;
        std::shared_ptr<ShaderProgram> shaderProgram;
        bool scaleToScreen = false;

        void tick(const float &delta) override;

        void init() override;

        void draw() override;
    public:
        using Object::Object;

        [[nodiscard]] bool isScaleToScreen() const;

        void setScaleToScreen(const bool &scaleToScreen);

        [[nodiscard]] const Vector2 &getOrigin() const;
        void setOrigin(const Vector2 &origin);

        explicit Object2D(Screen *screen, const std::vector<Vector2> &points, const Vector2 &origin,
                          std::shared_ptr<ShaderProgram> &&shader = []{ return std::make_shared<SolidColor>(
                                  Vector4(0.8f, 0.3f, 0.02f, 1.0f),
                                  "default.vert",
                                  "default.frag");}(),
                          const bool &isStatic = true,
                          const std::vector<unsigned int> &drawOrder = std::vector<unsigned int>(0U));

        void onDestroy() override;

        /**
         * Sets location in absolute screen coordinates
         * @param newLocation new screen coords
         */
        void setLocation(const Vector2& newLocation);

        [[nodiscard]] Vector2 getLocation() const { return this->origin; }

        /**
         * The default size is (1.0, 1.0). This new size should also be in percentages
         * @param newScale
         */
        void setScale(const Vector2& newScale);

        /**
         * Rotate an object on the z axis(the axis piercing the screen)
         * @param rotation in degrees
         */
        void setRotation(const float& rotation);
    };
}


#endif //ENPITSU_OBJECT2D_H
