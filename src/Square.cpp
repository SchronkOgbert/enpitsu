#include "enpitsu/objects/Square.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{
    Square::Square(enpitsu::Screen *screen, const double &size, const Vector2 &origin, std::shared_ptr<ShaderProgram> &&shader) :
            Triangles2D(screen,
                        {Vector2(0, 0), Vector2(size, 0), Vector2(size, size), Vector2(0, size)},
                        origin,
                        std::forward<std::shared_ptr<ShaderProgram>>(shader),
                        true,
                        {0, 1, 2, 0, 2, 3}
            )
    {

    }
} // enpitsu