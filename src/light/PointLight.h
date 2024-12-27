#pragma once
#include <glm/glm.hpp>
#include "Light.h"

class PointLight: public Light
{
protected:
     glm::vec4 m_Position;
public:
    void SetPosition(glm::vec3 position)
    {
        m_Position = glm::vec4(position, 1.0f);
    }
};