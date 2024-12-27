#pragma once
#include <vector>
#include <webgpu/webgpu.hpp>
#include "geometry/Geometry.h"
#include "render/RenderPassSubmitter.h"
#include "UI.h"
#include "ui/Interactions.h"
#include "Scene.h"
#include "ui/Interactions.h"
#include "render/GeometryRendererCommand.h"
#include "render/SupportTextureRendererCommand.h"
#include "render/CompositeRendererCommand.h"
#include "render/SceneRendererCommand.h"
#include "render/RayRendererCommand.h"


using namespace wgpu;
class SceneRender
{
private:
    GeometryRendererCommand m_GeometryRendererCommand;
    SupportTextureRendererCommand m_SupportTextureRendererCommand;
    CompositeRendererCommand m_CompositeRendererCommand;
    SceneRendererCommand m_SceneRendererCommand;
    RayRendererCommand m_RayRendererCommand;
    

    void RenderShadowMaps() 
    {}
    void RenderReflections()
    {}
    void RenderPickLayer()
    {}
public:

    void RenderMultipassMaterials()
    {
        //TODO
    }

    void RenderPostProcessing()
    {
        //TODO
    }

    void Wait()
    {
        // TODO
    }
    void RenderUICommands()
    {
        
    }
    void RenderGeometryRendererCommands()
    {
        m_GeometryRendererCommand.Render();
        Wait();
    }

    void RenderSupportTextureRendererCommands()
    {
        // shadow maps
        // reflections
        // pickers
        m_SupportTextureRendererCommand.Render();
        Wait();
    }
    void RenderCompositeRendererCommands()
    {
        m_CompositeRendererCommand.Render();
        Wait();
    }

    void RenderSceneRendererCommands()
    {
        m_SceneRendererCommand.Render();
        //
        Wait();
    }

    void RenderRayRendererCommands()
    {
        m_RayRendererCommand.Render();
    }
    void Render() 
    {
        //RenderGeometryRendererCommands();
        RenderSupportTextureRendererCommands();
        //RenderSceneRendererCommands();
        RenderRayRendererCommands();
        RenderCompositeRendererCommands();
        RenderUICommands();

        //RenderShadowMap(m_Geos);
        //RenderGeometry(m_Geos);
        wgpuSurfacePresent(WGPUContext::surface);
    }


    static SceneRender * Get()
    {
        static SceneRender render;
        return &render;
    }
};