//
// Created by weekendUM on 2/5/2023.
//

#ifndef LIBTEST_TEXTURE2D_H
#define LIBTEST_TEXTURE2D_H

#include "glad/glad.h"
#include "memory"


namespace enpitsu
{
    class Texture2D
    {
        GLuint ID;
        GLenum type;
        int width;
        int height;
        int columnCount;
    public:
        Texture2D(const char *textureFile);

        unsigned char *readTextureFile(const char *filename);

        int getWidth() const;

        int getHeight() const;
    };
}


#endif //LIBTEST_TEXTURE2D_H
