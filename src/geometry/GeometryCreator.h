#pragma once
#include "Geometry.h"
#include <memory>
#include <any>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "../enums/ObjectType.h"
#include "../enums/TextureType.h"
#include "../mesh/MeshCreator.h"
#include "../material/BaseMaterial.h"

class GeometryCreator
{
private:
    ObjectType m_Type;
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
    std::shared_ptr<BaseMaterial> m_Material = nullptr;
    std::map<std::string, std::any> m_Properties;
    glm::vec3 m_Pos = glm::vec3(0);
    glm::vec3 m_Scale = glm::vec3(1);
public:
    GeometryCreator() {}
    static std::shared_ptr<GeometryCreator> Builder()
    {
        return std::make_shared<GeometryCreator>();
    }
    GeometryCreator * SetType(ObjectType type)
    {
        m_Type = type;
        return this;
    }

    GeometryCreator * SetPosition(glm::vec3 pos)
    {
        m_Pos = pos;
        return this;
    }

    GeometryCreator * SetScale(glm::vec3 scale)
    {
        m_Scale = scale;
        return this;
    }
    GeometryCreator * SetMaterial(std::shared_ptr<BaseMaterial> m)
    {
        m_Material = m;
        return this;
    }

    GeometryCreator * AddMesh(float * vertices, int* indices, int verticesCount, int indicesCount, VertexDescriptor desc)
    {

        std::shared_ptr<Mesh> mesh = MeshCreator::CreateMesh(vertices, indices, verticesCount, indicesCount, desc);
        m_Meshes.emplace_back(mesh);
        return this;
    }

    GeometryCreator * AddProperties(std::string key, std::any value)
    {
        m_Properties[key] = value;
        return this;
    }

    std::shared_ptr<Geometry> Build()
    {
        std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();
        for (auto & mesh: m_Meshes)
        {
            geometry.get()->AddMesh(mesh);
        }
        if (m_Material != nullptr)
        {
            geometry.get()->UpdateMaterial(m_Material);
        }
        geometry.get()->properties = m_Properties;
        geometry.get()->SetPosition(m_Pos);
        geometry.get()->Scale(m_Scale);
        return geometry;
    }
    

};
