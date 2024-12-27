#pragma once
#include <imgui.h>
#include <fmt/format.h>
#include "camera/Camera.h"
class Controls
{
public:

    void Render() {
        ImGui::Begin("Camera Position: ");
        glm::vec3 pos = Camera::Get()->GetPosition();
        std::string s = fmt::format("{:.2f}, {:.2f}, {:.2f}", pos.x, pos.y, pos.z);
        ImGui::Text(s.c_str());
        ImGui::End();
    }
    static Controls * Get()
    {
        static Controls c;
        return &c;
    }
};