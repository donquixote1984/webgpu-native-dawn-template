
#include <imgui.h>
#include "./Application.h"
#include "UI.h"
#include "ui/MouseDispatcher.h"

bool Application::Initialize()
{
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, "WebGPU", nullptr, nullptr);

    if (!m_Window) {
        std::cerr << "Could not open window!" << std::endl;
        glfwTerminate();
        return false;
    }


    WGPUContext::Create(m_Window);
    WGPUPipelineInitator::Init();
    SceneLoader::GetInstance()->Load();

 //   Camera *camera = Camera::Get();
    MouseDispatcher *dispatcher = MouseDispatcher::Get();
//    auto *submitter = PickerSubmitter::Get();
    glfwSetWindowUserPointer(m_Window, dispatcher);
	glfwSetCursorPosCallback(m_Window, MouseDispatcher::cursorPosCallback);
    glfwSetMouseButtonCallback(m_Window, MouseDispatcher::mouseButtonCallback);

    UI::Get()->Init(m_Window);
    
    return true;
}
bool Application::IsRunning()
{
    return !glfwWindowShouldClose(m_Window);
}
void Application::Terminate()
{
    glfwDestroyWindow(m_Window);
    WGPUContext::Release();
    UI::Get()->Release();
    glfwTerminate();
}

void Application::MainLoop()
{
    glfwPollEvents();

    Camera *cam = Camera::Get();
    cam->OnUpdate(m_Window);
    /*WGPUTextureView targetView = WGPUContext::GetNextSurfaceTextureView();
    if (!targetView) 
    {
        return;
    }
    */
    
    Submit();


    WGPUContext::device.tick();
}

void Application::Submit()
{

    /*update scene*/
    Scene::GetInstance()->Loop();

}


Application * Application::GetInstance()
{
    static Application app;
    return &app;
}