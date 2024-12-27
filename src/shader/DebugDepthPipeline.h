#pragma once
#include "BasePipeline.h"

class DebugDepthPipeline: public BasePipeline
{
public:
    DebugDepthPipeline();
    virtual void CreatePipeline() override;
    virtual void CreateBindGroupLayout() override;
    static DebugDepthPipeline * Get()
    {
        static DebugDepthPipeline pipeline;
        return &pipeline;
    }
};
