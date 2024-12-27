#pragma once
#include "BaseMaterial.h"
#include "../ui/PickerPipeline.h"
#include "phases/PickerRenderPhase.h"

class PickerMaterial: public BaseMaterial
{
public:
    PickerMaterial();
    static PickerMaterial* Get()
    {
        static PickerMaterial pickerMaterial;
        return &pickerMaterial;
    }

    //void SetBindGroupToRenderPass(RenderPassEncoder renderPass, int uniformIndex) override
    //{
        //BindDynamicGroupToRenderPass(renderPass, uniformIndex);
    //}
};