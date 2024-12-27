#pragma once
#include "DebugWindowRenderPhase.h"
#include "../../shader/DebugDepthPipeline.h"
class DebugDepthRenderPhase: public DebugWindowRenderPhase
{
public:
    DebugDepthRenderPhase();
    virtual void CreateTextureBindGroup() override;
};