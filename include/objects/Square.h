//
// Created by weekendUM on 2/8/2023.
//

#ifndef LIBTEST_SQUARE_H
#define LIBTEST_SQUARE_H

#include "Triangles2D.h"
#include "shading/ShaderProgram.h"

namespace enpitsu
{

    class Square : public Triangles2D
    {
    public:
        /**
         * makes a square on the screen
         * @param screen the screen that made it
         * @param size the length of the lines in pixels
         */
        Square(enpitsu::Screen *screen, const double &size, const Vector2 &origin, ShaderProgram* shader = new SolidColor(Vector4(0.0f, 128, 0.0f, 255)));
    };

} // enpitsu

#endif //LIBTEST_SQUARE_H
