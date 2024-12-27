#pragma once
#include "../shader/TexturedGeometryPipeline.h"
#include "../shader/SampleColoredPipeline.h"
#include "../ui/PickerPipeline.h"
#include "../shadow/ShadowMapCSMPipeline.h"
#include "../shader/DebugWindowPipeline.h"
#include "../shader/DebugShadowPipeline.h"
#include "../shader/DebugDepthPipeline.h"
#include "../shader/RaytracingSimplePipeline.h"

class WGPUPipelineInitator
{
public:
    static void Init()
    {
        SampleColoredPipeline::Get()->Create();
        TexturedGeometryPipeline::Get()->Create();
        PickerPipeline::Get()->Create();
        ShadowMapCSMPipeline::Get()->Create();
        DebugWindowPipeline::Get()->Create();
        DebugShadowPipeline::Get()->Create();
        DebugDepthPipeline::Get()->Create();
        RaytracingSimplePipeline::Get()->Create();
    }
};