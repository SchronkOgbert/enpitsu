#include "enpitsu/objects/Sprite.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{
    Sprite::Sprite(enpitsu::Screen *screen, std::shared_ptr<Texture2DShader> &&shader, const bool &isStatic,
                   const Vector2 &origin) :
            Triangles2D(screen,
                        {
                                Vector2(0, 0),
                                Vector2(0, static_cast<GLfloat >(shader->getWidth())),
                                Vector2(static_cast<GLfloat >(shader->getHeight()),
                                        static_cast<GLfloat >(shader->getWidth())),
                                Vector2(static_cast<GLfloat >(shader->getHeight()), 0)
                        },
                        origin,
                        std::forward<std::shared_ptr<ShaderProgram>>(shader),
                        isStatic,
                        {
                                0, 1, 2, 0, 2, 3
                        }
            )
    {
        textureObject = shader.get();
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