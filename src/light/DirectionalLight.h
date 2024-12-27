#pragma once
#include "Light.h"
#include <vector>
#include "../base/Constants.h"
#include "../uniforms/LightUniform.h"

class DirectionalLightCSM
{
public:
    float lvls[constants::MAX_CSM_LVL - 1] =  {0.05f, .1f, .3f}; // camera far plane set to fixed 200
    std::vector<float> m_ShadowCascadeLevels;
    glm::mat4 shadowMapMatrices[constants::MAX_CSM_LVL];

    DirectionalLightCSM();

};

class DirectionalLight: public Light
{
protected:
    glm::vec4 m_Direction;
    DirectionalLightCSM m_CSM;
public:
    void SetDirection(glm::vec3 direction)
    {
        m_Direction = glm::vec4(direction, 1.0f);
    }

    glm::mat4 GetLightSpaceMatrix(float farPlane, float nearPlane);
    DirectionalLightCSM& GetCSM()
    {
        return m_CSM;
    }

    std::vector<float> GetShadowCascadeLvls()
    {
        return m_CSM.m_ShadowCascadeLevels;
    }

    void CalculateShadowMapMatrices();

    DirectionalLightUniform ToUniform();
};

