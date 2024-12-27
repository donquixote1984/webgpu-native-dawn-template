#pragma once

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Light
{
protected:
   
    glm::vec3 m_Color;

public:
    void SetColor(glm::vec3 color)
    {
        m_Color = color;
    }
};