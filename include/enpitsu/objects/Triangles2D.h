#ifndef ENPITSU_TRIANGLES2D_H
#define ENPITSU_TRIANGLES2D_H

#include "Object2D.h"

namespace enpitsu
{

    class Triangles2D : public Object2D
    {
    public:
        using Object2D::Object2D;
        Triangles2D(Screen* screen) = delete;

    protected:
        void draw() override;
    };

} // enpitsu

#endif //ENPITSU_TRIANGLES2D_H
