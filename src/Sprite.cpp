//
// Created by weekendUM on 2/5/2023.
//

#include "Sprite.h"

namespace enpitsu
{
    Sprite::Sprite(enpitsu::Screen *screen, Texture2D *textureObject) : Object(screen)
    {
        this->textureObject = std::unique_ptr<Texture2D>(textureObject);
    }

    int Sprite::getWidth() const
    {
        return textureObject->getWidth();
    }

    int Sprite::getHeight() const
    {
        return textureObject->getHeight();
    }
} // enpitsu