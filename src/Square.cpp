//
// Created by weekendUM on 2/8/2023.
//

#include "Square.h"

namespace enpitsu
{
    Square::Square(enpitsu::Screen *screen, const double &size, const Vector2 &origin) :
            Triangles2D(screen,
                        {Vector2(0, 0), Vector2(size, 0), Vector2(size, size), Vector2(0, size)},
                        origin,
                        new SolidColor(Vector4(0.0f, 128, 0.0f, 255)),
                        true,
                        {0, 1, 2, 0, 2, 3}
            )
    {

    }
} // enpitsu