#ifndef ENPITSU_SPRITE_H
#define ENPITSU_SPRITE_H

#include "Triangles2D.h"
#include "enpitsu/shading/Texture2DShader.h"

namespace enpitsu
{

    class Sprite : public Triangles2D
    {
    protected:
        Texture2DShader* textureObject;
    public:
        Sprite(enpitsu::Screen *screen, std::shared_ptr<Texture2DShader> &&shader, const bool &isStatic, const Vector2 &origin);

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;

    protected:
    public:
        void init() override;

        ~Sprite() override;

    protected:
        void draw() override;
    };

} // enpitsu

#endif //ENPITSU_SPRITE_H
