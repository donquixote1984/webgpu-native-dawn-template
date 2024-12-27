#pragma once
#include "../shadow/ShadowMapCSMPipeline.h"
#include "../material/ShadowMapCSMMaterial.h"
#include "../geometry/Geometry.h"

class ShadowRenderer
{
public:
    void UpdateModel();
    virtual void UpdateBuffers() 
    {}

    virtual void SetMaterial() 
    {
        //m_Material = ShadowMapCSMMaterial::Get();
    }
};