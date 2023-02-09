//
// Created by weekendUM on 2/5/2023.
//

#include "Sprite.h"
#include "Bell/Core.h"

using bell::core::println;

namespace enpitsu
{
    Sprite::Sprite(enpitsu::Screen *screen, Texture2D *textureObject) :
            Triangles(screen,
                      {
                              Vector2(0, 0),
                              Vector2(0, static_cast<GLfloat >(textureObject->getWidth())),
                              Vector2(static_cast<GLfloat >(textureObject->getHeight()),
                                      static_cast<GLfloat >(textureObject->getWidth())),
                              Vector2(static_cast<GLfloat >(textureObject->getHeight()), 0)
                      },
                      new SolidColor(Vector4(0.5f, 0.0f, 0.0f, 1.0f)),
                      true,
                      {
                              0, 1, 2, 0, 2, 3
                      }
            )
    {
        this->
                textureObject = std::unique_ptr<Texture2D>(textureObject);
        println("created sprite");
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
        Triangles::draw();
//        println("drawing sprite");
    }

    void Sprite::init()
    {
        Object2D::init();
        println("init sprite");
    }

} // enpitsu