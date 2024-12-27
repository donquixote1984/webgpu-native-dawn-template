#pragma once
#include "ScreenRenderPhase.h"
#include "../../shadow/ShadowMapCSMPipeline.h"
class ShadowMapCSMPhase: public ScreenRenderPhase
{
public:
    ShadowMapCSMPhase();
    std::vector<uint32_t> GetDynamicOffsetsAndCSM(uint16_t index, int csmIndex);
    void RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) override;
};
