#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Scene.h"
#include "mesh/Mesh.h"
#include "base/Vertex.h"
#include "mesh/MeshCreator.h"
#include "enums/ObjectType.h"
#include "data/Cube.h"
#include "data/SampleTexture.h"
#include "light/PointLight.h"
#include "light/DirectionalLight.h"
#include "geometry/GeometryCreator.h"
#include "material/MaterialCreator.h"
#include "loader/ObjLoader.h"
#include "tinyobjloader/tiny_obj_loader.h"
#include "ray/RaySceneLoader.h"

using namespace tinyobj;
class SceneLoader
{
public:
    void Load();
    static SceneLoader * GetInstance();
};