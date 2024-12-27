#pragma once
#include "BaseMaterial.h"
#include "phases/ShadowMapCSMPhase.h"
class ShadowMapCSMMaterial: public BaseMaterial
{
public:
    ShadowMapCSMMaterial()
    {
        std::shared_ptr<ScreenRenderPhase> renderPhase2 = std::make_shared<ShadowMapCSMPhase>();
        m_ScreenPhases.push_back(renderPhase2);
    }

    static ShadowMapCSMMaterial* Get()
    {
        static ShadowMapCSMMaterial material;
        return &material;
    }

    void SetShadowTextureView(TextureView &textureView)
    {
        
    }
    //void SetBindGroupToRenderPass(RenderPassEncoder renderPass, int uniformIndex) override
    //{
        //BindDynamicGroupToRenderPass(renderPass, uniformIndex);
    //}
};