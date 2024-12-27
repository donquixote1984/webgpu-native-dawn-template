#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "../initiator/WGPUContext.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

struct CameraSettings
{
    float nearPlane = 0.1f;
    float farPlane = 200.0f;
    float zoom = 45.0f;
};

struct CameraWorldCorner
{
    glm::vec4 corners[8];
    const glm::vec3 Center() const
    {
        //return (glm::vec3(backLeftBottom) + glm::vec3(backLeftTop) + glm::vec3(backRightBottom) + glm::vec3(backRightTop) + glm::vec3(frontLeftBottom) + glm::vec3(frontLeftTop) + glm::vec3(frontRightBottom) + glm::vec3(frontRightTop))/8.0f ;
        glm::vec4 c = glm::vec4(0.0f);
        for (int i = 0; i < 8; i++)
        {
            c += corners[i];
        }

        c /= 8;
        return c;
    }
    const glm::vec4 operator[](int x) const
    {
        if (x > 7) {
            return corners[0];
        }
        return corners[x];
    }
};


class Camera
{
private:
    glm::vec3 m_Position = glm::vec3(.0f,5.0f, 8.0f);
    glm::vec3 m_Offset = glm::vec3(.0f, .0f, .0f);
    glm::vec3 m_RotateBasePosition = glm::vec3(.0f, .0f, .0f);
    glm::vec3 m_CamFront = glm::vec3(.0f, .0f, -1.0f);
    glm::vec3 m_InitCamFront = glm::vec3(.0f, .0f, -1.0f);
    glm::vec3 m_CamUp = glm::vec3(.0f, 1.0f, .0f);
    glm::vec3 m_Translate = glm::vec3(0.0);
    glm::vec3 m_InitPos;
    float m_FocalLength = 0.0f;

    CameraSettings m_Settings;
    glm::mat4 m_Projection;

    bool m_FirstMouse = true;
    float m_LastMouseX = WGPUContext::SCREEN_WIDTH / 2;
    float m_LastMouseY = WGPUContext::SCREEN_HEIGHT / 2;
    bool m_YInversed = false;

    float m_RotateY = 0.0f;
    float m_RotateX = 0.0f;

public:
    Camera()
    {
        m_Projection = glm::perspective(glm::radians(m_Settings.zoom), (float)WGPUContext::SCREEN_WIDTH/ (float)WGPUContext::SCREEN_HEIGHT, m_Settings.nearPlane, m_Settings.farPlane);
    }
    static Camera * Get()
    {
        static Camera c;
        return &c;
    }

    void SetPosition(glm::vec3 pos)
    {
        m_Position = pos;
    }
    const glm::vec3 GetPosition() const
    {
        return m_Position;
    }
    glm::mat4 GetView()
    {
        return glm::lookAt(m_Position, m_Position + m_CamFront, m_CamUp);
    }
    const glm::mat4 GetProjection() const
    {
        return m_Projection;
    }

    const CameraSettings GetCameraSettings() const
    {
        return m_Settings;
    }

    void SetInitPosition(glm::vec3 pos)
    {
        m_Position = pos;
        m_InitPos = pos;
        m_Offset.y = pos.y;
        if (pos.x == 0.0f && pos.y == 0.0f && pos.z == 0.0f) 
        {
            m_InitCamFront = m_CamFront = glm::vec3(0, -1, 0);
        } else 
        {
            m_InitCamFront = m_CamFront = glm::normalize(-pos);
        }

        m_FocalLength = glm::length(pos);
        m_Position = -m_FocalLength * m_CamFront;
    }

    void ResetMouse()
    {
	    m_FirstMouse = true;
    }

    void onProcessInput(GLFWwindow *window);
    void onMouseMove(double x, double y);
    void OnUpdate(GLFWwindow *window);


    void OnMouse(GLFWwindow *window, double xpos, double ypos)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && (
            glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || 
            glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS
        ))  
        {
            this->onMouseMove(xpos, ypos);
        } else 
        {
            this->ResetMouse();
        }
    }

    CameraWorldCorner GetFrustumCornersWorldSpace(glm::mat4 projection)
    {
        CameraWorldCorner cwc;
        const auto inv = glm::inverse(projection * GetView());
        
        int index = 0;
        for (unsigned int x = 0; x < 2; ++x)
        {
            for (unsigned int y = 0; y < 2; ++y)
            {
                for (unsigned int z = 0; z < 2; ++z)
                {
                    const glm::vec4 pt = inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                    cwc.corners[index] = pt / pt.w;
                    index += 1;
                }
            }
        }
        return cwc;
    }
    CameraWorldCorner GetFrustumCornersWorldSpace(float nearPlane, float farPlane)
    {
	    glm::mat4 proj = glm::perspective(glm::radians(m_Settings.zoom), (float)WGPUContext::SCREEN_WIDTH / (float) WGPUContext::SCREEN_HEIGHT, nearPlane, farPlane);
	    return GetFrustumCornersWorldSpace(proj);
    }

    void UpdateScene();
};