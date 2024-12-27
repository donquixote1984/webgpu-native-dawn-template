#pragma once
#include <vector>
#include "Scene.h"

using namespace std;
class SceneUI
{
public:
    static Geometry * GetSelectedGeometry()
    {
        for(auto geo : Scene::GetInstance()->GetGeometries())
        {
            if (geo.get()->uiStatus.selected == true)
            {
                return geo.get();
            }
        }
        return nullptr;
    }

    static void SelectGeometry(int index)
    {
        if (index == -1)
        {
            return;
        }
        Scene::GetInstance()->LoopGeometries([&](vector<std::shared_ptr<Geometry>> geos){
            for (auto geo: geos)
            {
                if (geo.get()->GetUniformIndex() == index)
                {
                    geo.get()->uiStatus.selected = true;
                } else {
                    geo.get()->uiStatus.selected = false;
                }
            }
        });
    }

    static void UnSelectGeometry()
    {
        Scene::GetInstance()->LoopGeometries([&](vector<std::shared_ptr<Geometry>> geos){
            for (auto geo: geos)
            {
                geo.get()->uiStatus.selected = false;
            }
        });
    }

    
    static SceneUI * Get()
    {
        static SceneUI ui;
        return &ui;
    }
};