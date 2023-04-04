//
// Created by weekendUM on 2/5/2023.
//

#include "enpitsu/objects/Sprite.h"

namespace enpitsu
{
    Sprite::Sprite(enpitsu::Screen *screen, Texture2DShader *shader, const bool &isStatic, const Vector2 &origin) :
            Triangles2D(screen,
                        {
                              Vector2(0, 0),
                              Vector2(0, static_cast<GLfloat >(shader->getWidth())),
                              Vector2(static_cast<GLfloat >(shader->getHeight()),
                                      static_cast<GLfloat >(shader->getWidth())),
                              Vector2(static_cast<GLfloat >(shader->getHeight()), 0)
                      },
                        origin,
                        shader,
                        isStatic,
                        {
                              0, 1, 2, 0, 2, 3
                      }
            )
    {
        textureObject = shader;
    }

    int Sprite::getWidth() const
    {
        return textureObject->getWidth();
    }

    int Sprite::getHeight() const
    {
        return textureObject->getHeight();
    }

    void Sprite::draw()
    {
        Triangles2D::draw();
//        println("drawing sprite");
    }

    void Sprite::init()
    {
        Object2D::init();
    }

    Sprite::~Sprite()
    {
//        println("destroying sprite");
    }

} // enpitsu