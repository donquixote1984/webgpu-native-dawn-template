#pragma once

#include <webgpu/webgpu.hpp>
#include <unordered_map>
#include "../enums/ObjectType.h"
#include "../enums/TextureType.h"
#include "../shader/BasePipeline.h"
#include "../shader/VertexBasePipeline.h"
#include "../sampler/SamplerObject.h"
#include "phases/BackendRenderPhase.h"
#include "phases/ScreenRenderPhase.h"


using namespace wgpu;
class Geometry;
class BaseMaterial
{
protected:
    bool m_HasPrePass = false;
    std::vector<std::shared_ptr<BackendRenderPhase>> m_BackendPhases;
    std::vector<std::shared_ptr<ScreenRenderPhase>> m_ScreenPhases;

    Buffer m_UniformBuffer = nullptr;
    BindGroup m_UniformBindGroup = nullptr;
    void CreateUniformBindGroup();
    Geometry * m_GeoRef;

public:
    ~BaseMaterial();
   
    const std::vector<std::shared_ptr<BackendRenderPhase>> & GetBackendPhases()
    {
        return m_BackendPhases;
    }
    void SetGeometry(Geometry * geo)
    {
        m_GeoRef = geo;
    }
    const std::vector<std::shared_ptr<ScreenRenderPhase>> & GetScreenPhases()
    {
        return m_ScreenPhases;
    }
    bool HasPrePass()
    {
        return m_HasPrePass;
    }

    std::shared_ptr<ScreenRenderPhase> GetLastScreenPhase()
    {
        return m_ScreenPhases[m_ScreenPhases.size() - 1];
    }
    //virtual void SetBindGroupToRenderPass(RenderPassEncoder, int uniformIndex) = 0;
};
