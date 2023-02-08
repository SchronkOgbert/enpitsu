//
// Created by weekendUM on 2/8/2023.
//

#ifndef LIBTEST_SQUARE_H
#define LIBTEST_SQUARE_H

#include "Triangles.h"

namespace enpitsu
{

    class Square : public Triangles
    {
    public:
        /**
         * makes a square on the screen
         * @param screen the screen that made it
         * @param size the length of the lines in pixels
         */
        explicit Square(Screen* screen, const double& size = 128);
    };

} // enpitsu

#endif //LIBTEST_SQUARE_H
