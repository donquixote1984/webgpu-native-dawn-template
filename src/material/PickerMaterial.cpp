#include "PickerMaterial.h"

PickerMaterial::PickerMaterial()
{
    //m_Pipeline = PickerPipeline::Get();

    BindGroupDescriptor desc = {};
    std::shared_ptr<ScreenRenderPhase> renderPhase2 = std::make_shared<PickerRenderPhase>();
    m_ScreenPhases.push_back(renderPhase2);
}