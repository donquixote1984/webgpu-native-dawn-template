#pragma once
#include "DebugWindowRenderPhase.h"
#include "../../shader/DebugShadowPipeline.h"
#include "../../shadow/SceneShadowMapCSMTexture.h"
class DebugShadowRenderPhase: public DebugWindowRenderPhase
{
public:
    DebugShadowRenderPhase();
    virtual void CreateTextureBindGroup() override;
};