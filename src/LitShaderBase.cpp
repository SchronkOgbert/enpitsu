#include "enpitsu/shading/LitShaderBase.h"
#include "enpitsu/GL/VBO.h"
#include "enpitsu/helpers/Exception.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "fmt/core.h"

namespace enpitsu
{
    LitShaderBase::LitShaderBase(const Vector4 &color, bool flat) :
            SolidColor(color, "default3D.vert", "default3D.frag")
    {

    }

    void LitShaderBase::calculateNormals(bool flat)
    {
        if (flat)
        {
            // TODO: replace this with something that makes sense
            // this is probably the most inefficient algorithm known to man
            auto normalsRes = generateFlatNormals(*(this->vertices), *(this->indices));
            normals = normalsRes.first;
            *vertices = normalsRes.second;
            PLOGD << "Indices before flat shading: " << *(this->indices);
            this->indices->clear();
            for(int i = 0; i < this->vertices->size(); i++)
            {
                this->indices->emplace_back(i);
            }
        } else
        {
            throw Exception("Smooth normals haven't been implemented yet");
        }
    }

    void LitShaderBase::Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                               const bool &isStatic)
    {
        if(normals.empty())
        {
            calculateNormals(flatShading);
        }
        normalsVBO = std::make_unique<VBO>(&normals[0], sizeof(GLfloat) * normals.size(), VBO::objectLayout::NORMAL, isStatic);
        SolidColor::Create(*(this->vertices), *(this->indices), vertexSize, isStatic);
        vao->LinkVBO(*normalsVBO);
        normalsVBO->Unbind();
        try
        {
            this->updateVec4Uniform("lightColor", glm::value_ptr(screen->getLightColor() / 255.0f));
            this->updateVec3Uniform("lightPos", glm::value_ptr(screen->getLightPosition()));
            this->updateVec3Uniform("cameraPosition", glm::value_ptr(screen->getCamera3D()->getPosition()));
        }
        catch(BadUniform& e)
        {
            PLOGW << e.what();
        }
    }

    bool LitShaderBase::isFlatShading() const
    {
        return flatShading;
    }

    void LitShaderBase::setFlatShading(bool flatShading)
    {
        LitShaderBase::flatShading = flatShading;
    }

    void LitShaderBase::setScreen(Screen *screen)
    {
        LitShaderBase::screen = screen;
    }

    LitShaderBase::~LitShaderBase()
    {
        normalsVBO->Delete();
    }
} // enpitsu