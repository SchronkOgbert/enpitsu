#ifndef ENPITSU_CAMERA2D_H
#define ENPITSU_CAMERA2D_H

#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/objects/ControlObject.h"
#include "glm/ext/matrix_clip_space.hpp"
namespace enpitsu
{

    class Camera2D : public ControlObject
    {
        bool update{false};

        float getOffsetFromCenter() const;
    protected:
        Vector2 size;
        Vector2 position;
        static constexpr Vector3 orientation{0, 0, -1};
        Vector3 up{0, 1, 0};
        glm::mat4 projection;
        glm::mat4 view{1};
        float unitScale{128};

    protected:
        void init() override;

        void screenSizeChanged(const Vector2 &newSize) override;

        void updateMatrix();

    public:
        Camera2D() = delete;

        Camera2D(Screen* screen, const Vector2& position, const Vector2& size);

        [[nodiscard]] float getUnitScale() const;

        void setUnitScale(float unitScale);
    };

} // enpitsu

#endif //ENPITSU_CAMERA2D_H
