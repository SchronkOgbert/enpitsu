//
// Created by weekendUM on 2/13/2023.
//

#ifndef LIBTEST_TEXTURE2DSHADER_H
#define LIBTEST_TEXTURE2DSHADER_H

#include "ShaderProgram.h"
#include "Texture2D.h"

namespace enpitsu
{

    class Texture2DShader : public ShaderProgram
    {
    protected:
        std::unique_ptr<Texture2D> textureObject;
        std::unique_ptr<VBO> textureCoords;
        std::vector<GLfloat > coordData{0, 0, 0, 1, 1, 1, 1, 0};
    public:
        explicit Texture2DShader(Texture2D* textureObject);

        Texture2DShader(const char *vertexFile, const char *fragmentFile, Texture2D* textureObject);

        [[nodiscard]] int getWidth() const
        {
            return textureObject->getWidth();
        }

        [[nodiscard]] int getHeight() const
        {
            return textureObject->getHeight();
        }

        void Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                    const bool &isStatic) override;

        void Bind();
    };

} // enpitsu

#endif //LIBTEST_TEXTURE2DSHADER_H
