#pragma once
#include <webgpu/webgpu.hpp>
#include <memory>
#include "../initiator/WGPUContext.h"
#include "../geometry/Geometry.h"
#include "../data/Canvas.h"
#include "../geometry/GeometryCreator.h"
#include "../material/phases/DebugShadowRenderPhase.h"

using namespace wgpu;
class DebugShadow
{
private:
    std::shared_ptr<Geometry> m_Geometry;
    DebugShadowRenderPhase m_RenderPhase;
public:

    DebugShadow()
    {
        m_Geometry = GeometryCreator::Builder().get()->AddMesh(data::quarterCanvasVertices, data::canvasIndices, 4, 6, VertexDescriptor::VERTEX_BASE)
        ->Build();
    }

    ~DebugShadow()
    {}

    static DebugShadow * Get()
    {
        static DebugShadow debugShadow;
        return &debugShadow;
    }
    void Render(RenderPassEncoder &renderPass)
    {
        void * context[1] = {(void*)m_Geometry.get()};
        m_RenderPhase.RenderByRenderPass(renderPass, context);
    }
};