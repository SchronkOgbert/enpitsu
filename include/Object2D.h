//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_OBJECT2D_H
#define LIBTEST_OBJECT2D_H

#include "Object.h"
#include "GeometryEssentials.h"
#include <vector>

namespace enpitsu
{
    class Object2D : public Object
    {
        std::vector<Vector2> points;
    public:
        using Object::Object;

        Object2D(Screen *screen, const std::vector<Vector2> &points, bool isStatic);

    protected:
        virtual void draw() override;
    };
}


#endif //LIBTEST_OBJECT2D_H
