#pragma once
#include <vector>
#include "PointLight.h"
#include "DirectionalLight.h"
#include "../base/Constants.h"
#include "../uniforms/CSMUniform.h"
#include "../camera/Camera.h"
#include "../uniforms/CSMUniform.h"
#include "../uniforms/LightUniform.h"
#include "../initiator/WGPUContext.h"
struct SceneLights
{
    std::vector<PointLight> pointlights;
    std::vector<DirectionalLight> directionallights;
    
    void SyncDirectinalLightsMatToCSM()
    {
        Camera *cam = Camera::Get();
        float camNearPlane = cam->GetCameraSettings().nearPlane;
        float camFarPlane = cam->GetCameraSettings().farPlane;

        glm::mat4 shadowMapMatrices[directionallights.size() * constants::MAX_CSM_LVL];
        for (int i = 0; i < directionallights.size(); i++)
        {
            DirectionalLight &light = directionallights[i];
            std::vector<float>  csmlvls = light.GetShadowCascadeLvls();
            shadowMapMatrices[i * constants::MAX_CSM_LVL] = directionallights[i].GetLightSpaceMatrix(camNearPlane, csmlvls[0]);
            for (int j = 1; j < csmlvls.size(); j++)
            {
                shadowMapMatrices[i * constants::MAX_CSM_LVL + j] = directionallights[i].GetLightSpaceMatrix(csmlvls[j-1], csmlvls[j]);
            }
            shadowMapMatrices[i * constants::MAX_CSM_LVL + csmlvls.size()] = directionallights[i].GetLightSpaceMatrix(csmlvls[csmlvls.size()-1], camFarPlane);
        }

        WGPUContext::queue.writeBuffer(CSMUniformBuffer::Get()->GetBuffer(), 0, shadowMapMatrices, sizeof(shadowMapMatrices));
    }

    void SyncToLightBuffer()
    {
        LightUniform lu;
        lu.dCount = directionallights.size();
        lu.pCount = pointlights.size();

        for (int i = 0; i < directionallights.size(); i++)
        {
            if (i >= constants::MAX_DIRECTIONAL_LIGHT)
            {
                break;
            }

            lu.directionalLights[i] = directionallights[i].ToUniform();
        }

        WGPUContext::queue.writeBuffer(LightUniformBuffer::Get()->GetBuffer(), 0, &lu, sizeof(LightUniform));
    }
};