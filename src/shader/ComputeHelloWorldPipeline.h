#pragma once
#include "BaseComputePipeline.h"

class ComputeHelloWorldPipeline: public BaseComputePipeline
{
public:
    ComputeHelloWorldPipeline();
    virtual void CreateBindGroupLayout() override;    
    virtual void CreatePipeline() override;
    static ComputeHelloWorldPipeline *Get()
    {
        static ComputeHelloWorldPipeline pipeline;
        return &pipeline;
    }
};