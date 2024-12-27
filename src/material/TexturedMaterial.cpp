#include "TexturedMaterial.h"
#include "../mesh/Mesh.h"

TexturedMaterial::TexturedMaterial()
{
    std::shared_ptr<ScreenRenderPhase> renderPhase1 = std::make_shared<TextureRenderPhase>();
    std::shared_ptr<BackendRenderPhase> renderPhase2 = std::make_shared<SampleBackendRenderPhase>();
    m_BackendPhases.push_back(renderPhase2);
    m_ScreenPhases.push_back(renderPhase1);
}
TexturedMaterial::~TexturedMaterial()
{}