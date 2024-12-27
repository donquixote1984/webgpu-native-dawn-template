#include "ComputeConsoleApplication.h"


bool ComputeConsoleApplication::Initialize()
{

    WGPUContext::Create(nullptr);
    WGPUComputePipelineInitiator::Init();

    return true;
}

void ComputeConsoleApplication::MainCompute()
{
    TestComputeRenderPhase phase ;
    phase.Compute();

}

void ComputeConsoleApplication::Terminate()
{
    WGPUContext::Release();
}