#ifndef ENPITSU_SQUARE_H
#define ENPITSU_SQUARE_H

#include "Triangles2D.h"
#include "enpitsu/shading/ShaderProgram.h"

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

#endif //ENPITSU_SQUARE_H
