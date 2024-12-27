#pragma once
#include "BasePipeline.h"

class DebugShadowPipeline: public BasePipeline
{
public:
    DebugShadowPipeline();
    virtual void CreatePipeline() override;
    virtual void CreateBindGroupLayout() override;
    static DebugShadowPipeline * Get()
    {
        static DebugShadowPipeline pipeline;
        return &pipeline;
    }
};
