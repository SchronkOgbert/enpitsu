#include "enpitsu/objects/Cube.h"

namespace enpitsu
{
    Cube::Cube(Screen *screen, const Vector3 &origin, const std::shared_ptr<ShaderProgram> &shader) :
            Triangles3D(screen, new std::vector<Vector3>{
                                {-1, -1, 0},
                                {-1, -1, -1},
                                {0,  -1, -1},
                                {0,  -1, 0},
                                {-1, 0,  0},
                                {-1, 0,  -1},
                                {0,  0,  -1},
                                {0,  0,  0}
                        },
                        origin,
                        {1, 1, 1},
                        shader,
                        isStatic,
                        new std::vector<unsigned>{
                                0, 1, 2,
                                0, 2, 3,
                                0, 4, 7,
                                0, 7, 3,
                                3, 7, 6,
                                3, 6, 2,
                                2, 6, 5,
                                2, 5, 1,
                                1, 5, 4,
                                1, 4, 0,
                                4, 5, 6,
                                4, 6, 7
                        }
            )
    {

    }
} // enpitsu