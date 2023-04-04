#ifndef LIBTEST_TRIANGLES3D_H
#define LIBTEST_TRIANGLES3D_H

#include "Object3D.h"

namespace enpitsu
{

    class Triangles3D : public Object3D
    {
    public:
        using Object3D::Object3D;
        Triangles3D(Screen* screen) = delete;

    protected:
        void draw() override;
    };

} // enpitsu

#endif //LIBTEST_TRIANGLES3D_H
