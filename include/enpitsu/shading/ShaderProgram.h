#ifndef ENPITSU_SHADERPROGRAM_H
#define ENPITSU_SHADERPROGRAM_H

#include "enpitsu/helpers/defines.h"
#include "enpitsu/helpers/Exception.h"
#include "enpitsu/GL/VAO.h"
#include "enpitsu/GL/EBO.h"

namespace enpitsu
{
    class BadShaderCompile : public Exception
    {
    public:
        explicit BadShaderCompile(const char *msg) :
                Exception(msg)
        {}
    };

    class BadShaderLink : public Exception
    {
    public:
        explicit BadShaderLink(const char *msg) :
                Exception(msg)
        {}
    };

    class BadShaderSource : public Exception
    {
    public:
        explicit BadShaderSource(const char *msg) :
                Exception(msg)
        {}
    };

    class BadShaderInfo : public Exception
    {
    public:
        BadShaderInfo() : Exception("The vertices or indices provided are empty")
        {}
    };

    class BadUniform : public Exception
    {
    public:
        BadUniform() = delete;
        BadUniform(const char* uniform) : Exception(format("Uniform {} does not exist", uniform)){}
    };

    class ShaderProgram
    {
    protected:
        GLuint ID;
        GLuint vertexShader;
        GLuint fragmentShader;
        bool initialized{false};

        //shader data
        std::unique_ptr<VAO> vao;
        std::unique_ptr<VBO> vertexPosition;
        std::unique_ptr<EBO> ebo;

        std::vector<GLfloat> *vertices; // reference only, non-owning
        std::vector<GLuint> *indices; // reference only, non-owning
    public:
        [[nodiscard]] const std::unique_ptr<VAO> &getVao() const
        {
            return vao;
        }

        [[nodiscard]] const std::unique_ptr<VBO> &getVertexPosition() const
        {
            return vertexPosition;
        }

        [[nodiscard]] const std::unique_ptr<EBO> &getEbo() const
        {
            return ebo;
        }

        void setVao(VAO *vao)
        {
            this->vao = std::unique_ptr<VAO>(vao);
        }

        void setVertexPosition(VBO *vertexPosition)
        {
            this->vertexPosition = std::unique_ptr<VBO>(vertexPosition);
        }

        void setEbo(EBO *ebo)
        {
            ShaderProgram::ebo = std::unique_ptr<EBO>(ebo);
        }

        [[nodiscard]] bool isInitialized() const;

        void setInitialized(bool initialized);

    private:
        static char *readShaderFile(const char *filename);

        void hasCompiled(const GLuint &shader);

        void hasLinked();

        int getUnifromLocation(const char* uniformName) const;

    public:
        explicit ShaderProgram(const char *vertexFile = "default.vert", const char *fragmentFile = "default.frag");

        virtual void
        Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
               const bool &isStatic);

        virtual void Delete();

        virtual void Bind();

        virtual void Unbind();

        virtual ~ShaderProgram();

        [[nodiscard]] GLuint getId() const;

        // uniform updaters

        void updateMat4UniformF(const std::string& uniformName, const float* value) const;

        void updateVec3Uniform(const std::string& uniformName, const float* value) const;

        void updateVec4Uniform(const std::string& uniformName, const float value[]) const;

        void updateFloatUniform(const std::string& uniformName, const float& value) const;

        [[nodiscard]] std::vector<GLfloat> *getVertices() const;

        void setVertices(std::vector<GLfloat> *vertices);

        [[nodiscard]] std::vector<GLuint> *getIndices() const;

        void setIndices(std::vector<GLuint> *indices);
    };
}


#endif //ENPITSU_SHADERPROGRAM_H
