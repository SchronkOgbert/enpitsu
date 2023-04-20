#ifndef ENPITSU_LINES2D_H
#define ENPITSU_LINES2D_H

#include "Object2D.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"

namespace enpitsu
{
    class BadLines2DException : public Exception
    {
    public:
        BadLines2DException() : Exception("Lines2D must have at least 2 points of type Vector2")
        {}
    };

    class Lines2D : public Object2D
    {
    protected:
        void draw() override;

    public:
        Lines2D(Screen *screen, const std::vector<Vector2> &points,
                std::shared_ptr<ShaderProgram> &&shader = newShader<SolidColor>(Vector4(128.0f, 0.0f, 0.0f, 255)), const bool &isStatic = true);
        Lines2D(Screen* screen) = delete;
    };

} // enpitsu

#endif //ENPITSU_LINES2D_H
