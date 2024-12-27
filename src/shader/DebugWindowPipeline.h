#pragma once
#include "BasePipeline.h"

class DebugWindowPipeline: public BasePipeline
{
public:
    DebugWindowPipeline();
    virtual void CreatePipeline() override;
    virtual void CreateBindGroupLayout() override;
    static DebugWindowPipeline * Get()
    {
        static DebugWindowPipeline pipeline;
        return &pipeline;
    }
};
