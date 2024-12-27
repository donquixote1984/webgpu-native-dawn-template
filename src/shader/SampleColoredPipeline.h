#pragma once
#include "VertexBasePipeline.h"
class SampleColoredPipeline: public VertexBasePipeline
{
public:
    SampleColoredPipeline();
    virtual void CreateBindGroupLayout() override;
    virtual void CreatePipeline() override;
    static SampleColoredPipeline * Get()
    {
        static SampleColoredPipeline pipeline;
        return &pipeline;
    }
};