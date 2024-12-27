#pragma once
#include "RendererCommand.h"
#include "../Scene.h"
#include "../material/phases/RenderPhaseCommandIssuer.h"
class GeometryRendererCommand: public RendererCommand
{
public:
    void Render()
    {
        auto &geos = Scene::GetInstance()->GetGeometries();
        for (auto &geo : geos)
        {
            RenderPhaseCommandIssuer::IssueCmd(geo->GetCurrentMaterial()->GetBackendPhases());
        }
    }
};