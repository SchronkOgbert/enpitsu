//
// Created by weekendUM on 2/8/2023.
//

#include "Square.h"

namespace enpitsu
{
    Square::Square(enpitsu::Screen *screen, const double &size) :
            Triangles(screen,
                      {Vector2(0, 0), Vector2(size, 0), Vector2(size, size), Vector2(0, size)},
                      new SolidColor(Vector4(0.5f, 0.0f, 0.0f, 1.0f)),
                      true,
                      {0, 1, 2, 0, 2, 3}
            )
    {

    }
} // enpitsu