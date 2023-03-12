//
// Created by weekendUM on 2/5/2023.
//

#ifndef LIBTEST_SPRITE_H
#define LIBTEST_SPRITE_H

#include "Triangles2D.h"
#include "Texture2DShader.h"

namespace enpitsu
{

    class Sprite : public Triangles2D
    {
    protected:
        Texture2DShader* textureObject;
    public:
        Sprite(enpitsu::Screen *screen, Texture2DShader *shader, const bool &isStatic, const Vector2 &origin);

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;

    protected:
    public:
        void init() override;

        ~Sprite() override;

        void resize() override;

    protected:
        void draw() override;
    };

} // enpitsu

#endif //LIBTEST_SPRITE_H
