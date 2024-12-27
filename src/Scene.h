#pragma once
#include <vector>
#include <webgpu/webgpu.hpp>
#include <memory>
#include <functional>
#include "geometry/Geometry.h"
#include "uniforms/ViewProjectionUniform.h"
#include "uniforms/CameraPositionUniform.h"
#include "uniforms/ScreenUniform.h"
#include "uniforms/LightUniform.h"
#include "uniforms/CSMUniform.h"
#include "camera/Camera.h"
#include "light/SceneLights.h"
#include "ui/Interactions.h"


using namespace wgpu;
using namespace std;

class Scene
{
private:
    SceneLights m_Lights;
    vector<std::shared_ptr<Geometry>> m_Geos;

    
    TextureView m_TargetView = nullptr;
    TextureView m_DepthView = nullptr;

    Interactions m_Interactions;
    bool m_ShouldUpdate = true;
public:

    Scene();
    ~Scene();
    void Init();
    void Loop();
    static Scene * GetInstance();
    void CreateDepthTextureView();
    
    void AddGeometry(std::shared_ptr<Geometry> geometry);

    void SetGlobalUniformBufferData();

    void SetViewProjection();
    void SetLightBuffer();
    void SetCountBuffer();
    void SetCameraPosition();
    void SetScreenBuffer();
    void SetTimeBuffer();
    void SetCSM();

    void AddPointLight(PointLight pointlight);
    void AddDirectionalLight(DirectionalLight directionallight);
    vector<std::shared_ptr<Geometry>> & GetGeometries()
    {
        return m_Geos;
    }

    const Interactions & GetInteractions() const
    {
        return m_Interactions;
    }
    void OnMouseClick(GLFWwindow* window, double xpos, double ypos)
    {
        m_Interactions.mouse.clicked = true;
        m_Interactions.mouse.clickXpos = xpos;
        m_Interactions.mouse.clickYpos = ypos;
    }

    void LoopGeometries(function<void(vector<std::shared_ptr<Geometry>>)> callback)
    {
        callback(m_Geos);
    }

    void ShouldUpdate()
    {
        m_ShouldUpdate = true;
    }
};
