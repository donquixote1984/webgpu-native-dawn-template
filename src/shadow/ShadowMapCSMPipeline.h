#pragma once
#include "../shader/VertexBasePipeline.h"
#include "../uniforms/CSMUniform.h"

class ShadowMapCSMPipeline: public VertexBasePipeline
{

public:
    ShadowMapCSMPipeline();
    virtual void CreateBindGroupLayout() override;
    virtual void CreatePipeline() override;

    static ShadowMapCSMPipeline * Get()
    {
        static ShadowMapCSMPipeline pipeline;
        return &pipeline;
    }
};