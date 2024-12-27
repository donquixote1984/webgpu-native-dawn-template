#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_wgpu.h>
#include <backends/imgui_impl_glfw.h>
#include <webgpu/webgpu.hpp>
#include "initiator/WGPUContext.h"
#include "Controls.h"
#include "ui/Picker.h"
#include "Gizmo.h"


class UI
{
private:
    Gizmo m_Gizmo;
public:
    void Init(GLFWwindow * window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::GetIO().DisplayFramebufferScale = {1, 1};
        ImGui_ImplGlfw_InitForOther(window, true);
        // ImGui_ImplWGPU_Init(WGPUContext::device, 3, TextureFormat::BGRA8Unorm, TextureFormat::Depth32Float);
        ImGui_ImplWGPU_InitInfo info;
        info.NumFramesInFlight = 3;
        info.DepthStencilFormat = TextureFormat::Depth32Float;
        info.Device = WGPUContext::device;
        info.RenderTargetFormat = TextureFormat::BGRA8Unorm;
        ImGui_ImplWGPU_Init(&info);
        //io.DisplaySize = ImVec2(WGPUContext::SCREEN_WIDTH / io.DisplayFramebufferScale, WGPUContext::SCREEN_HEIGHT / io.DisplayFramebufferScale);
       
        //io.DisplaySize = {WGPUContext::SCREEN_WIDTH / 2, WGPUContext::SCREEN_HEIGHT / 2};
        m_Gizmo.Init(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
    }
    void Release()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplWGPU_Shutdown();
    }
    void Update(RenderPassEncoder &renderPass);
     
    static UI * Get()
    {
        static UI ui;
        return &ui;
    }
};