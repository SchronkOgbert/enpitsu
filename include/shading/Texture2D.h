//
// Created by weekendUM on 2/5/2023.
//

#ifndef LIBTEST_TEXTURE2D_H
#define LIBTEST_TEXTURE2D_H

#include "helpers/defines.h"
#include "ShaderProgram.h"
#include "helpers/Exception.h"

namespace enpitsu
{
    class BadTextureException : public Exception
    {
    public:
        BadTextureException() : Exception("Texture could not be loaded")
        {}
    };

    class Texture2D
    {
        enum DisplayType
        {
            NEAREST,
            LINEAR
        }displayType;
        GLuint ID{};
        GLenum type{};
        int width{};
        int height{};
        int columnCount{};
    public:

        explicit Texture2D(const char *textureFile);

        unsigned char *readTextureFile(const char *filename);

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;

        void changeDisplayType(const DisplayType &displayType);

        void Bind() const;

        void Unbind() const;

//        void BuildUnit(ShaderProgram* shaderProgram, )

        virtual ~Texture2D();
    };
}


#endif //LIBTEST_TEXTURE2D_H
