//
// Created by weekendUM on 2/5/2023.
//

#ifndef LIBTEST_SPRITE_H
#define LIBTEST_SPRITE_H

#include "Object.h"
#include "Texture2D.h"

namespace enpitsu
{

    class Sprite : public Object
    {
    protected:
        std::unique_ptr<Texture2D> textureObject;
    public:
        Sprite(Screen* screen, Texture2D* textureObject);

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;
    };

} // enpitsu

#endif //LIBTEST_SPRITE_H
