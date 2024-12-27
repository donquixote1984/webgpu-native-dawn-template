#include "Gizmo.h"
#include "SceneUI.h"
#include "Scene.h"
#include "geometry/Geometry.h"
#include "camera/Camera.h"

void Gizmo::Render()
{

    CheckOperations();
    ImGuizmo::SetOrthographic(false);

    ImGuizmo::BeginFrame();
    ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    auto viewMatrix = Camera::Get()->GetView();
    auto perspective = Camera::Get()->GetProjection();
    Geometry *selectedGeometry = SceneUI::Get()->GetSelectedGeometry();

    if (selectedGeometry != nullptr)
    {
        auto &modelMat = selectedGeometry->GetModelMat();
        // ImGuizmo::Manipulate(cameraView, cameraProjection, ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, matrix, NULL,  NULL, NULL, NULL);
        ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(perspective), m_CurrentGizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(modelMat), NULL, NULL, NULL, NULL);

        //std::cout << modelMat[2][3] << std::endl;
       
        //selectedGeometry->Translate(trs);
        
        if (ImGuizmo::IsUsing() && ImGuizmo::IsOver())
        {
            WriteBack(modelMat);
        }
    }
}

void Gizmo::WriteBack(glm::mat4 &modelMat)
{
    glm::vec3 trs, rots, scs;
    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(modelMat), glm::value_ptr(trs), glm::value_ptr(rots), glm::value_ptr(scs));
    Geometry *selectedGeometry = SceneUI::Get()->GetSelectedGeometry();
    selectedGeometry->SetModelMat(glm::value_ptr(modelMat));
    /*
    if (m_CurrentGizmoOperation == ImGuizmo::TRANSLATE)
    {
        selectedGeometry->Translate(trs);

    }

    if (m_CurrentGizmoOperation == ImGuizmo::SCALE)
    {
        selectedGeometry->Scale(scs);
        std::cout << scs[0] << " " << scs[1] << " " << scs[2] << std::endl;
    }

    if (m_CurrentGizmoOperation == ImGuizmo::ROTATE)
    {
        // eular
        std::cout << rots[0] << " " << rots[1] << " " << rots[2] << std::endl;
        selectedGeometry->Rotate(rots);
    }
    */
}
void Gizmo::CheckOperations()
{

    if (ImGui::IsKeyPressed(ImGuiKey_W))
    {
        m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
    }

    if (ImGui::IsKeyPressed(ImGuiKey_E))
    {
        m_CurrentGizmoOperation = ImGuizmo::SCALE;
    }

    if (ImGui::IsKeyPressed(ImGuiKey_R))
    {
        m_CurrentGizmoOperation = ImGuizmo::ROTATE;
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Q))
    {
        m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
    }
}