#pragma once
#include <webgpu/webgpu.hpp>

#include "../shader/BasePipeline.h"
#include "../shader/Shader.h"

using namespace wgpu;

class PickerPipeline: public BasePipeline
{
private:
public:
    PickerPipeline();
    virtual void CreateBindGroupLayout() override;
    virtual void CreatePipeline() override;


    static PickerPipeline * Get()
    {
        static PickerPipeline pickerPipeline;
        return &pickerPipeline;
    }

};