//
// Created by weekendUM on 2/8/2023.
//

#ifndef LIBTEST_SOLIDCOLOR_H
#define LIBTEST_SOLIDCOLOR_H

#include "ShaderProgram.h"
#include "GeometryEssentials.h"

namespace enpitsu
{

    class SolidColor : public ShaderProgram
    {
        Vector4 color;
    public:
        explicit SolidColor(const Vector4& rgbaColor);

        void Create() override;
    };

} // enpitsu

#endif //LIBTEST_SOLIDCOLOR_H
