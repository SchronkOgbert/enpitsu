#ifndef ENPITSU_LINE2D_H
#define ENPITSU_LINE2D_H

#include "Object2D.h"

namespace enpitsu
{
    class BadLine2DException : public Exception
    {
    public:
        BadLine2DException() : Exception("Line2D must have exactly 2 points of type Vector2")
        {}
    };
    class Line2D : public Object2D
    {
    public:
        Line2D(Screen *screen, const std::vector<Vector2> &points, const bool &isStatic = true);

    protected:
        void draw() override;
    };
}


#endif //ENPITSU_LINE2D_H
