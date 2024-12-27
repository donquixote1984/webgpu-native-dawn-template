#include "Pipeline.h"
#include "../initiator/WGPUContext.h"

Pipeline::~Pipeline()
{}

void Pipeline::Release()
{
    if (pipeline != nullptr)
    {
        pipeline.release();
        pipeline = nullptr;
    }

    /*if (bindGroup != nullptr)
    {
        bindGroup.release();
        bindGroup = nullptr;
    } */
}

