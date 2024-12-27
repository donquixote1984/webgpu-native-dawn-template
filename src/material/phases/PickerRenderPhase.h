#pragma once

#include "../../ui/PickerPipeline.h"
#include "../../uniforms/PickerUniform.h"
#include "ScreenRenderPhase.h"

class PickerRenderPhase: public ScreenRenderPhase 
{
protected:
    
public:
    PickerRenderPhase();
    virtual void RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) override;
    virtual void CreateBindGroups() override;
    void UpdatePickerColor(Geometry * geo);
};