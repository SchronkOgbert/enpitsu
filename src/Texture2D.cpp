//
// Created by weekendUM on 2/5/2023.
//

#define STB_IMAGE_IMPLEMENTATION // this piece of shit needs to be here for stb to work

#include "Texture2D.h"
#include "stb_image.h"
#include "Bell/Core.h"

using bell::core::println;

enpitsu::Texture2D::Texture2D(const char *textureFile)
{
    auto textureData = readTextureFile(textureFile);

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    Bind();
    changeDisplayType(DisplayType::LINEAR);
    glTexImage2D
            (
                    GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    width,
                    height,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    textureData
            );
    glGenerateMipmap(GL_TEXTURE_2D);
    Unbind();
    stbi_image_free(textureData);
    println("loaded texture");
}

void enpitsu::Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void enpitsu::Texture2D::changeDisplayType(const enpitsu::Texture2D::DisplayType &displayType)
{
    // TODO: this will surely need more work
    this->displayType = displayType;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    this->displayType == NEAREST ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    this->displayType == NEAREST? GL_NEAREST : GL_NEAREST_MIPMAP_LINEAR);
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

void enpitsu::Texture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

enpitsu::Texture2D::~Texture2D()
{
    glDeleteTextures(1, &ID);
}