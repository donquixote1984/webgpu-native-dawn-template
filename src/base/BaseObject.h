#pragma once

#include <memory>
#include "../enums/ObjectType.h"
#include "Vertices.h"
#include "Indexes.h"
class BaseObject
{
protected:
    ObjectType m_Type;
    std::shared_ptr<Vertices> m_Vertices;
    
public:
    BaseObject()
    {}
    Buffer GetBuffer() 
    {
        return m_Vertices.get()->GetBuffer();
    }

    Buffer GetIndexBuffer()
    {
        return m_Vertices.get()->GetIndexBuffer();
    }
    size_t GetCount()
    {
        return m_Vertices.get()->GetCount();
    }
    size_t GetIndexCount()
    {
        return m_Vertices.get()->GetIndexCount();
    }

    void SetVertices(std::shared_ptr<Vertices> v)
    {
        m_Vertices = std::move(v);
    }
    void SetObjectType(ObjectType t) 
    {
        m_Type = t;
        //m_Material.SetPipeline(WGPUPipelinePool::pipelines[t]);
    }
};