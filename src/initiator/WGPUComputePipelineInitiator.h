#pragma once
#include "../shader/ComputeHelloWorldPipeline.h"

class WGPUComputePipelineInitiator
{
public:
    static void Init()
    {
        ComputeHelloWorldPipeline::Get()->Create();
    }
};