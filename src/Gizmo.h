#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <glm/glm.hpp>
#include <ImGuizmo.h>

class Gizmo
{
private:
    ImGuizmo::OPERATION m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
    ImGuizmo::MODE m_CurrentGizmoMode = ImGuizmo::LOCAL;
    float m_SizeX;
    float m_SizeY;
    void CheckOperations();
    void WriteBack(glm::mat4 &);
public:
    void Init(float sizeX, float sizeY)
    {
        ImGuizmo::SetOrthographic(false);
        m_SizeX = sizeX;
        m_SizeY = sizeY;
    }
    void Render();
};