#include "enpitsu/objects/Pyramid.h"

namespace enpitsu
{

    Pyramid::Pyramid(Screen *screen, Vector3 origin, ShaderProgram *shader, const bool &isStatic) :
            Triangles3D(screen, new std::vector<Vector3>{
                                {100, 100, 10},
                                {100, 100, 30},
                                {300, 100, 30},
                                {300, 100, 10},
                                {100, 300, 25}
                        },
                        origin,
                        {1, 1, 1},
                        shader,
                        isStatic,
                        new std::vector<unsigned>{0, 1, 2,
                                                  0, 2, 3,
                                                  0, 1, 4,
                                                  1, 2, 4,
                                                  2, 3, 4,
                                                  3, 0, 4}
            )
    {

    }
} // enpitsu