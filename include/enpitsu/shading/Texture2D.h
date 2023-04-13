#ifndef ENPITSU_TEXTURE2D_H
#define ENPITSU_TEXTURE2D_H

#include "enpitsu/helpers/defines.h"
#include "ShaderProgram.h"
#include "enpitsu/helpers/Exception.h"

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


#endif //ENPITSU_TEXTURE2D_H
