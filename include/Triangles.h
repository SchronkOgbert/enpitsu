//
// Created by weekendUM on 2/3/2023.
//

#ifndef LIBTEST_TRIANGLES_H
#define LIBTEST_TRIANGLES_H

#include "Object2D.h"

namespace enpitsu
{

    class Triangles : public Object2D
    {
    public:
        using Object2D::Object2D;

    protected:
        void draw() override;
    };

} // enpitsu

#endif //LIBTEST_TRIANGLES_H
