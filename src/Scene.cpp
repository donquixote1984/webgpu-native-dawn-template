#include "Scene.h"
#include "SceneRender.h"
Scene::Scene()
{
}
Scene::~Scene()
{
}

void Scene::Init()
{
}


void Scene::Loop()
{
    //RenderPassEncoder renderPass = BeginRenderPass(encoder);
    if (!m_ShouldUpdate) {
        return;
    }
    m_ShouldUpdate = false;
    SetGlobalUniformBufferData();

    //m_Render.Render(m_Geos, m_Interactions);
    SceneRender::Get()->Render();
    m_Interactions.Reset();
    //m_RenderPassCollection.EndRenderPass();

}

Scene * Scene::GetInstance()
{
    static Scene scene;
    return &scene;
}

void Scene::AddGeometry(std::shared_ptr<Geometry> geometry)
{
    m_Geos.push_back(std::move(geometry));
}

void Scene::SetGlobalUniformBufferData()
{
    SetViewProjection();
    SetLightBuffer();
    SetCountBuffer();
    SetCameraPosition();
    SetScreenBuffer();
    SetTimeBuffer();
    // TODO add shadow toggle
    SetCSM();
}

void Scene::SetTimeBuffer()
{
    float time = static_cast<float>(glfwGetTime());
    Buffer timeBuffer = TimeUniformBuffer::Get()->GetBuffer();
    WGPUContext::queue.writeBuffer(timeBuffer, 0, &time, sizeof(float));
}

void Scene::SetCSM()
{
    //CSMUniform csmUniform;
    //Buffer csmBuffer = CSMUniformBuffer::Get()->GetBuffer();
    m_Lights.SyncDirectinalLightsMatToCSM();
}

void Scene::SetViewProjection()
{
    ViewProjectionUniform vpu;
    vpu.view = Camera::Get()->GetView();
    vpu.projection = Camera::Get()->GetProjection();
    vpu.invview = glm::inverse(vpu.view);
    vpu.invprojection = glm::inverse(vpu.projection);
    Buffer vpBuffer = ViewProjectionUniformBuffer::Get()->GetBuffer();
    WGPUContext::queue.writeBuffer(vpBuffer, 0, &vpu, sizeof(vpu));
}

void Scene::SetCameraPosition()
{
    Buffer camPosBuffer = CameraPositionUniformBuffer::Get()->GetBuffer();
    glm::vec4 pos = glm::vec4(Camera::Get()->GetPosition(), 1.0f);
    WGPUContext::queue.writeBuffer(camPosBuffer, 0, &pos, sizeof(glm::vec4));
}


void Scene::SetScreenBuffer()
{
    Buffer screenBuffer = ScreenUniformBuffer::Get()->GetBuffer();
    ScreenUniform screen;
    screen.width = WGPUContext::SCREEN_WIDTH;
    screen.height = WGPUContext::SCREEN_HEIGHT;
    screen.aspectRatio = (float)screen.width / (float)screen.height;

    WGPUContext::queue.writeBuffer(screenBuffer, 0, &screen, sizeof(ScreenUniform));
}

void Scene::SetLightBuffer()
{
    m_Lights.SyncToLightBuffer();
}

void Scene::AddPointLight(PointLight pointlight)
{
    this->m_Lights.pointlights.push_back(pointlight);
}
void Scene::AddDirectionalLight(DirectionalLight directionallight)
{
    this->m_Lights.directionallights.push_back(directionallight);
}
void Scene::SetCountBuffer()
{
    CountUniform cu;
    cu.pointLightCount = this->m_Lights.pointlights.size();
    cu.directionalLightCount = this->m_Lights.directionallights.size();
    Buffer cBuffer = CountUniformBuffer::Get()->GetBuffer();
    WGPUContext::queue.writeBuffer(cBuffer, 0, &cu, sizeof(CountUniform));
}
