#include "DirectionalLight.h"
#include "../camera/Camera.h"

DirectionalLightCSM::DirectionalLightCSM()
{
    Camera *camera = Camera::Get();
    for (int i = 0; i < constants::MAX_CSM_LVL - 1 ; i++)
    {
        m_ShadowCascadeLevels.push_back(camera->GetCameraSettings().farPlane * lvls[i]);
    }
}


glm::mat4 DirectionalLight::GetLightSpaceMatrix(float nearPlane, float farPlane)
{
    Camera * camera = Camera::Get();
    const auto corners = camera->GetFrustumCornersWorldSpace(nearPlane, farPlane);
    glm::vec3 frustrumCenter = corners.Center();
    const auto lightView = glm::lookAt(frustrumCenter + glm::normalize(glm::vec3(m_Direction)), frustrumCenter, glm::vec3(.0f, 1.0f, .0f));

    float maxX= std::numeric_limits<float>::lowest();
    float minX= std::numeric_limits<float>::max();

    float maxY= std::numeric_limits<float>::lowest();
    float minY= std::numeric_limits<float>::max();

    float maxZ= std::numeric_limits<float>::lowest();
    float minZ= std::numeric_limits<float>::max();

    for (int i = 0; i < 8; i++)
    {
        const auto pos = lightView * corners[i];
        minX = std::min(pos.x, minX);
        maxX = std::max(pos.x, maxX);

        minY = std::min(pos.y, minY);
        maxY = std::max(pos.y, maxY);

        minZ = std::min(pos.z, minZ);
        maxZ = std::max(pos.z, maxZ);
    }

    constexpr float zMult = 10.0f;
    if (minZ < 0)
    {
        minZ *= zMult;
    }
    else
    {
        minZ /= zMult;
    }
    if (maxZ < 0)
    {
        maxZ /= zMult;
    }
    else
    {
        maxZ *= zMult;
    }

    const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
    return lightProjection * lightView;
}

void DirectionalLight::CalculateShadowMapMatrices()
{
    Camera *cam = Camera::Get();
    float camNearPlane = cam->GetCameraSettings().nearPlane;
    float camFarPlane = cam->GetCameraSettings().farPlane;
    m_CSM.shadowMapMatrices[0] = GetLightSpaceMatrix(camNearPlane, m_CSM.m_ShadowCascadeLevels[0]);
    for (int j = 1; j < m_CSM.m_ShadowCascadeLevels.size(); j++)
    {
        m_CSM.shadowMapMatrices[j] = GetLightSpaceMatrix(m_CSM.m_ShadowCascadeLevels[j-1], m_CSM.m_ShadowCascadeLevels[j]);
    }
    m_CSM.shadowMapMatrices[m_CSM.m_ShadowCascadeLevels.size()] = GetLightSpaceMatrix(m_CSM.m_ShadowCascadeLevels[m_CSM.m_ShadowCascadeLevels.size()-1], camFarPlane);
}

 DirectionalLightUniform DirectionalLight::ToUniform()
    {
        DirectionalLightUniform dlu;
        dlu.color = glm::vec4(m_Color, 1.0);
        dlu.direction = m_Direction;
        for (int i = 0; i < constants::MAX_CSM_LVL-1; i++)
        {
            dlu.csmLvlDist[i] = m_CSM.m_ShadowCascadeLevels[i];
        }
        dlu.csmLvlDist[constants::MAX_CSM_LVL-1] = Camera::Get()->GetCameraSettings().farPlane;
        CalculateShadowMapMatrices();
        memcpy(dlu.csm, m_CSM.shadowMapMatrices, sizeof(m_CSM.shadowMapMatrices));
        return dlu;
    }