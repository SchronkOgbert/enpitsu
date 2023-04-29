#include "enpitsu/objects/Pyramid.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{

    Pyramid::Pyramid(Screen *screen, Vector3 origin, const std::shared_ptr<ShaderProgram> &shader, const bool &isStatic) :
            Triangles3D(screen, new std::vector<Vector3>{
                                {-0.5, 0, 0.5},
                                {-0.5, 0, -0.5},
                                {0.5, 0, -0.5},
                                {0.5, 0, 0.5},
                                {0, 0.8, 0}
                        },
                        origin,
                        {1, 1, 1},
                        shader,
                        isStatic,
                        new std::vector<unsigned>{0, 1, 2,
                                                  0, 2, 3,
                                                  0, 4, 1,
                                                  1, 2, 4,
                                                  2, 3, 4,
                                                  3, 0, 4}
            )
    {

    }
} // enpitsu