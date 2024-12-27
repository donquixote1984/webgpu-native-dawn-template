#pragma once
#include <webgpu/webgpu.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "initiator/WGPUContext.h"
#include "initiator/WGPUComputePipelineInitiator.h"
#include "material/phases/TestComputeRenderPhase.h"

class ComputeConsoleApplication
{
public:
    bool Initialize();
    void Terminate();
    void MainCompute();
private:
public:
    static ComputeConsoleApplication * GetInstance()
    {
        static ComputeConsoleApplication app;
        return &app;
    }
};