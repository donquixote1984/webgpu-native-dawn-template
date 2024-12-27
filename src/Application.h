#pragma once
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <webgpu/webgpu.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "glfw3webgpu.h"
#include "shader/Shader.h"
#include "initiator/WGPUContext.h"
#include "initiator/WGPUPipelineInitiator.h"
#include "base/Vertices.h"
#include "SceneLoader.h"
#include "Scene.h"




class Application
{
public:
    bool Initialize();
    void Terminate();
    void MainLoop();
    bool IsRunning();
    
    GLFWwindow * m_Window;

private:
    void Submit();
public:
    static Application * GetInstance();
};