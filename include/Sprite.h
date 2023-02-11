//
// Created by weekendUM on 2/5/2023.
//

#ifndef LIBTEST_SPRITE_H
#define LIBTEST_SPRITE_H

#include "Triangles.h"
#include "Texture2D.h"

namespace enpitsu
{

    class Sprite : public Triangles
    {
    protected:
        std::unique_ptr<Texture2D> textureObject;
    public:
        Sprite(enpitsu::Screen *screen, Texture2D *textureObject, const bool &isStatic, const Vector2 &origin);

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;

    protected:
    public:
        void init() override;

    protected:
        void draw() override;
    };

} // enpitsu

#endif //LIBTEST_SPRITE_H
