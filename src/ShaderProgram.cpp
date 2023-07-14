#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/GL/Wrapper.h"
#include "enpitsu/helpers/Exception.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/shading/ShaderSources.h"
#include "fmt/format.h"
#include <chrono>
#include <memory>
#include <string>
#include <thread>

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

        vertexShader = callGLFunction(glCreateShader, GL_VERTEX_SHADER);
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

        if (!defaultVertex)
        {
            delete[] vertexData;
        }
        if (!defaultFrag)
        {
            delete[] fragmentData;
        }
    }

    void ShaderProgram::Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices,
                               const int &vertexSize,
                               const bool &isStatic)
    {
        if (vertices.empty() || indices.empty())
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
        hasLinked();
        hasCompiled(vertexShader);
        hasCompiled(fragmentShader);
        glUseProgram(ID);
        initialized = true;
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
        return strdup(buffer.c_str());
    }

    GLuint ShaderProgram::getId() const
    {
        return ID;
    }

    void ShaderProgram::hasCompiled(const GLuint &shader) const
    {
        int compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        auto glError = glGetError();
        if(glError != GL_NO_ERROR && !compiled)
        {
            PLOGE << GLErrors[glError];
            throw Exception(format("Error when checking shader: {}", GLErrors[glError].c_str()));
        }
        PLOGD << format("Compiled: {}", compiled);
        if (!compiled)
        {
            char shaderSource[1024];
            glGetShaderSource(shader, 1024, nullptr, shaderSource);
            PLOGE << format("Shader compile rc: {}", compiled);
            char shaderInfo[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, shaderInfo);
            PLOGW << format("Shader source:\n{}\n", shaderSource);
            PLOGE << shaderInfo;
            throw BadShaderCompile(shaderInfo);
        }
    }

    void ShaderProgram::hasLinked() const
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
        if(vao)
        {
            vao->Delete();
        }
        if(vertexPosition)
        {
            vertexPosition->Delete();
        }
        if(ebo)
        {
            ebo->Delete();
        }
    }

    void ShaderProgram::Unbind()
    {
        vao->Unbind();
        glUseProgram(0);
    }

    void ShaderProgram::updateMat4UniformF(const std::string &uniformName, const float *value)
    {
        glUniformMatrix4fv(getUniformLocation(uniformName.c_str()),
                           1, GL_FALSE, value);
    }

    void ShaderProgram::updateVec3Uniform(const std::string &uniformName, const float *value)
    {
        glUniform3fv(getUniformLocation(uniformName.c_str()), 1, value);
    }

    int ShaderProgram::getUniformLocation(const char *uniformName)
    {
        int location = -1;
        if(uniformsCache.find(uniformName) == uniformsCache.end())
        {
            location = glGetUniformLocation(this->getId(), uniformName);
            uniformsCache[uniformName] = location;
        }
        else
        {
            location = uniformsCache[uniformName];
        }
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

    void ShaderProgram::updateVec4Uniform(const std::string &uniformName, const float *value)
    {
        glUniform4fv(getUniformLocation(uniformName.c_str()), 1, value);
    }

    void ShaderProgram::updateFloatUniform(const std::string &uniformName, const float &value)
    {
        glUniform1f(getUniformLocation(uniformName.c_str()), value);
    }

    bool ShaderProgram::isInitialized() const
    {
        return initialized;
    }

    void ShaderProgram::setInitialized(bool initialized)
    {
        ShaderProgram::initialized = initialized;
    }
}