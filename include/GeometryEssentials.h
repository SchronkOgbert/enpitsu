//
// Created by weekendUM on 2/2/2023.
//

#ifndef LIBTEST_GEOMETRYESSENTIALS_H
#define LIBTEST_GEOMETRYESSENTIALS_H

namespace enpitsu
{
    struct Vector2
    {
        double x;
        double y;
        Vector2() = default;
        Vector2(const double &x, const double &y) : x(x), y(y)
        {}
    };

    struct Vector3
    {
        double x;
        double y;
        double z;

        Vector3() = default;

        Vector3(double x, double y, double z) : x(x), y(y), z(z)
        {}
    };

    struct Vector4
    {
        double x;
        double y;
        double z;
        double a;

        Vector4() = default;

        Vector4(double x, double y, double z, double a) : x(x), y(y), z(z), a(a)
        {}

        static float* toArray(const Vector4& obj);
    };
}

#endif //LIBTEST_GEOMETRYESSENTIALS_H
