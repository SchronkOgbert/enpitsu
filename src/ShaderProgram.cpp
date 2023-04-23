#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/shading/ShaderSources.h"

namespace enpitsu
{
    ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
    {
        const bool defaultVertex = defaultShaderSources->count(std::string(vertexFile));
        const bool defaultFrag = defaultShaderSources->count(std::string(fragmentFile));
        const char *vertexData = defaultVertex ?
                                 (*defaultShaderSources)[std::string(vertexFile)].c_str() :
                                 readShaderFile(vertexFile);
        const char *fragmentData = defaultFrag ?
                                   (*defaultShaderSources)[std::string(fragmentFile)].c_str() :
                                   readShaderFile(fragmentFile);

        if (strlen(vertexData) == 0)
        {
            throw BadShaderSource("Vertex shader source could not be loaded. Is the file path correct");
        }
        if (strlen(fragmentData) == 0)
        {
            throw BadShaderSource("Fragment shader source could not be loaded. Is the file path correct?");
        }

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        PLOGD << format("vertex shader: {}, fragment shader: {}", vertexShader, fragmentShader);
        PLOGD << "compiling shader " << ID << "(" << vertexFile << ")";
        ID = glCreateProgram();

        glShaderSource(vertexShader, 1, &vertexData, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentData, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);

        if(!defaultVertex)
        {
            delete[] vertexData;
        }
        if(!defaultFrag)
        {
            delete[] fragmentData;
        }
    }

    void ShaderProgram::Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices,
                               const int &vertexSize,
                               const bool &isStatic)
    {
        if(vertices.empty() || indices.empty())
        {
            throw BadShaderInfo();
        }
        setVao(new VAO(vertexSize));
        getVao()->Bind();
        setVertexPosition(new VBO(&vertices[0U], sizeof(vertices[0]) * vertices.size(),
                                  vertexSize == 2 ? VBO::objectLayout::VERTEX2D : VBO::objectLayout::VERTEX3D,
                                  isStatic));
        setEbo(new EBO(&indices[0U], sizeof(indices[0]) * indices.size(), isStatic));
        glLinkProgram(ID);
        hasCompiled(vertexShader);
        hasCompiled(fragmentShader);
        hasLinked();
        glUseProgram(ID);
    }

    void ShaderProgram::Delete()
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(ID);
    }

    char *ShaderProgram::readShaderFile(const char *filename)
    {
        PLOGD << "reading shader file " << filename;
        // TODO: replace this with something that runs in a reasonable amount of time
        std::ifstream fin(filename);
        std::string buffer;
        std::string lineBuffer;
        while (std::getline(fin, lineBuffer))
        {
            buffer += lineBuffer + "\n";
        }
        char *result = new char[buffer.size() + 1];
        strcpy(result, buffer.c_str());
        return result;
    }

    GLuint ShaderProgram::getId() const
    {
        return ID;
    }

    void ShaderProgram::hasCompiled(const GLuint &shader)
    {
        int compiled;
        glGetShaderiv(ID, GL_COMPILE_STATUS, &compiled);
        char shaderSource[1024];
        glGetShaderSource(shader, 1024, nullptr, shaderSource);
//        println("Shader source:\n------------------\n", shaderSource, "\n-----------------");
        if (!compiled)
        {
            char shaderInfo[1024];
            glGetShaderInfoLog(ID, 1024, nullptr, shaderInfo);
            PLOGE << shaderInfo;
            throw BadShaderCompile(shaderInfo);
        }
    }

    void ShaderProgram::hasLinked()
    {
        int linked;
        glGetProgramiv(ID, GL_LINK_STATUS, &linked);
        if (!linked)
        {
            char programInfo[1024];
            glGetProgramInfoLog(ID, 1024, nullptr, programInfo);
            throw BadShaderLink(programInfo);
        }
    }

    void ShaderProgram::Bind()
    {
        vao->Bind();
        glUseProgram(ID);
    }

    ShaderProgram::~ShaderProgram()
    {
//        println("destroy shader");
    }

    void ShaderProgram::Unbind()
    {
        vao->Unbind();
        glUseProgram(0);
    }

    void ShaderProgram::updateMat4UniformF(const std::string &uniformName, const float *value) const
    {
        glUniformMatrix4fv(getUnifromLocation(uniformName.c_str()),
                           1, GL_FALSE, value);
    }

    void ShaderProgram::updateVec3Uniform(const std::string &uniformName, const float *value) const
    {
        glUniform3fv(getUnifromLocation(uniformName.c_str()), 1, value);
    }

    int ShaderProgram::getUnifromLocation(const char *uniformName) const
    {
        int location = glGetUniformLocation(this->getId(), uniformName);
        if(location == -1) throw BadUniform(uniformName);
        return location;
    }

    std::vector<GLfloat> *ShaderProgram::getVertices() const
    {
        return vertices;
    }

    void ShaderProgram::setVertices(std::vector<GLfloat> *vertices)
    {
        ShaderProgram::vertices = vertices;
    }

    std::vector<GLuint> *ShaderProgram::getIndices() const
    {
        return indices;
    }

    void ShaderProgram::setIndices(std::vector<GLuint> *indices)
    {
        ShaderProgram::indices = indices;
    }

    void ShaderProgram::updateVec4Uniform(const std::string &uniformName, const float *value) const
    {
        glUniform4fv(getUnifromLocation(uniformName.c_str()), 1, value);
    }

    void ShaderProgram::updateFloatUniform(const std::string &uniformName, const float &value) const
    {
        glUniform1f(getUnifromLocation(uniformName.c_str()), value);
    }
}