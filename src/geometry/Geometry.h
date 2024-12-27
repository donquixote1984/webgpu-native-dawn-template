#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <any>
#include <vector>
#include "../mesh/Mesh.h"
#include "../material/BaseMaterial.h"
#include "../base/TransformObject.h"
#include "../ui/UIStatus.h"

class Geometry: public TransformObject
{
private:

    Indexes m_Index;
    std::shared_ptr<BaseMaterial> m_Material;
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
    glm::vec4 m_PickId;
    Geometry(Geometry &g) = delete;
public:
    UIStatus uiStatus;
    Geometry() {
        IncrementIndex();
        GeneratePickId();
    }
    std::map<std::string, std::any> properties;
    void UpdateMaterial(std::shared_ptr<BaseMaterial> m)
    {
        this->m_Material = m;
        this->m_Material->SetGeometry(this);
    }
    BaseMaterial * GetCurrentMaterial()
    {
        return m_Material.get();
    }
    int GetIndexCount()
    {
        return m_Meshes[0].get()->GetIndexCount();
    }

    void AddMesh(std::shared_ptr<Mesh> mesh)
    {
        m_Meshes.push_back(std::move(mesh));
    }
    const std::vector<std::shared_ptr<Mesh>> GetMeshes() const
    {
        return m_Meshes;
    }

    Buffer GetBuffer()
    {
        // TODO : merge all meshes buffer into one
        return m_Meshes[0].get()->GetBuffer();
    }

    Buffer GetIndexBuffer()
    {
        return m_Meshes[0].get()->GetIndexBuffer();
    }

    int GetUniformIndex()
    {
        return m_Index.uniformIndex;
    }

     void IncrementIndex()
    {
        m_Index.index = Indexes::IndexCounter()->index;
        m_Index.uniformIndex = Indexes::IndexCounter()->uniformIndex;
        Indexes::IndexCounter()->index += 1;
        Indexes::IndexCounter()->uniformIndex += 1;
    }

     void GeneratePickId()
    {
        int index = m_Index.index + 1;
        float r = (float)(index         & 0xFF) / 255.0;
        float g = (float)((index >> 8)  & 0xFF) / 255.0;
        float b = (float)((index >> 16) & 0xFF) / 255.0;
        float a = 1;

        m_PickId = glm::vec4(r, g, b, a);
        //WGPUContext::queue.writeBuffer(Picker::Get()->GetPickerBuffer(), );
    }
    glm::vec4 GetPickId()
    {
        return m_PickId;
    }

};