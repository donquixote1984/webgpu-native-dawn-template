#pragma once
#include "BasePipeline.h"
#include "../uniforms/ScreenUniform.h"
#include "../uniforms/BVHUniform.h"
#include "../uniforms/RayHitableUniform.h"
class RaytracingSimplePipeline: public BasePipeline
{
public:
    RaytracingSimplePipeline();
    virtual void CreatePipeline() override;
    virtual void CreateBindGroupLayout() override;
    static RaytracingSimplePipeline * Get()
    {
        static RaytracingSimplePipeline pipeline;
        return &pipeline;
    }
};