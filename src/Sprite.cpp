#include "enpitsu/objects/Sprite.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/Texture2DShader.h"

namespace enpitsu
{
    Sprite::Sprite(enpitsu::Screen *screen, std::shared_ptr<Texture2DShader> &&shader, const bool &isStatic,
                   const Vector2 &origin) :
            Triangles2D(screen,
                        {
                                Vector2(0, 0),
                                Vector2(static_cast<GLfloat >(shader->getWidth()), 0),
                                Vector2(static_cast<GLfloat >(shader->getWidth()),
                                        static_cast<GLfloat >(shader->getHeight())),
                                Vector2(0, static_cast<GLfloat >(shader->getHeight()))
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
    }

    void Sprite::onDestroy()
    {
        Object2D::onDestroy();
    }

    void Sprite::init()
    {
        Object2D::init();
    }

    Sprite::~Sprite()
    {

    }

} // enpitsu