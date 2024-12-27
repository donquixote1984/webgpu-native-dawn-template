#pragma once
#include "../Scene.h"
#include "RendererCommand.h"
#include "../passes/ShadowMapRenderPass.h"
#include "../material/ShadowMapCSMMaterial.h"
#include "../initiator/WGPUCommandSubmitter.h"
class ShadowMapRendererCommand:  public RendererCommand
{
private:
    ShadowMapRenderPass m_ShadowMapRenderPass;
public:
    virtual void Render() override;
};
