#pragma once
#include "../camera/Camera.h"
#include "PickerSubmitter.h"
using namespace std;
class MouseDispatcher
{
public:
    static MouseDispatcher* Get()
    {
        static MouseDispatcher mouseDispatcher;
        return &mouseDispatcher;
    }

    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
       // Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

        Camera *camera = Camera::Get();
       
        camera->OnMouse(window, xpos, ypos);
        
    }

    static bool byPassSceneClick(GLFWwindow *window)
    {
        std::vector<int> byPassKeys;
        byPassKeys.push_back(GLFW_KEY_LEFT_SUPER);
        byPassKeys.push_back(GLFW_KEY_LEFT_ALT);

        for (auto key: byPassKeys)
        {
            if (glfwGetKey(window, key) == GLFW_PRESS)
            {
                return true;
            }
        }

        return false;

    }
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        //PickerSubmitter *pickerSubmitter = PickerSubmitter::Get();

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
        {
            if (byPassSceneClick(window))
            {
                return;
            }

            Scene *scene = Scene::GetInstance();
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            scene->OnMouseClick(window, xpos, ypos);
        }
    }
};