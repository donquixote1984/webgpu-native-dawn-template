

#include "UI.h"
#include "Scene.h"
#include "SceneUI.h"


 void UI::Update(RenderPassEncoder &renderPass)
    {
        ImGui_ImplWGPU_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
       
        ImGuiIO& io = ImGui::GetIO();
        m_Gizmo.Render();
       
        ImGui::GetIO().DisplayFramebufferScale = {1, 1};
    // [...] Build our UI
        Controls::Get()->Render();
    // Draw the UI
        ImGui::EndFrame();
    // Convert the UI defined above into low-level drawing commands
        ImGui::Render();
    // Execute the low-level drawing commands on the WebGPU backend
        ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), renderPass);
    }