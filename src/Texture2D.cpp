//
// Created by weekendUM on 2/5/2023.
//

#include "Texture2D.h"
#include "stb_image.h"

enpitsu::Texture2D::Texture2D(const char *textureFile)
{
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto textureData = std::unique_ptr<unsigned char>(readTextureFile(textureFile));

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned char *enpitsu::Texture2D::readTextureFile(const char *filename)
{
    return stbi_load(filename, &width, &height, &columnCount, 0);
}

int enpitsu::Texture2D::getWidth() const
{
    return width;
}

int enpitsu::Texture2D::getHeight() const
{
    return height;
}
