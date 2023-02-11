//
// Created by weekendUM on 2/5/2023.
//

#ifndef LIBTEST_TEXTURE2D_H
#define LIBTEST_TEXTURE2D_H

#include "glad/glad.h"
#include "memory"
#include "ShaderProgram.h"


namespace enpitsu
{
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