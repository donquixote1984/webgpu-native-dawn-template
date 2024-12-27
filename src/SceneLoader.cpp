#include "SceneLoader.h"
#include <iterator>
#include <random>
#include <array>
#include <numeric>
#include <algorithm>
#include <boost/range/algorithm.hpp>


SceneLoader * SceneLoader::GetInstance()
{
    static SceneLoader loader;
    return &loader;
}

void SceneLoader::Load()
{
    //std::shared_ptr<float> vertices = std::shared_ptr<float>(new float[]{1,2,3});
    std::shared_ptr<float[]> vertices = std::shared_ptr<float[]>(new float[]{
        -0.5, -0.5, 0, 
        0.5, -0.5, 0,
        0.5, 0.5, 0,
        -0.5, 0.5, 0
    });

    std::shared_ptr<float[]> vertices2 = std::shared_ptr<float[]>(new float[]{
        -0.5, -0.5, 0, 
        0.5, -0.5, 0,
        0.5, 0.5, 0,
        -0.5, 0.5, 0
    });

    for (int i = 0; i < 12; i++)
    {
        if (vertices.get()[i] != 0)
        vertices.get()[i] = vertices.get()[i] * 0.5-0.25; 
    }

    for (int i = 0; i < 12; i++)
    {
        if (vertices2.get()[i] != 0)
        vertices2.get()[i] = vertices2.get()[i] * 0.5+0.25;
    }
    

/*
    std::shared_ptr<Mesh> mesh = MeshCreator::CreateMesh(vertices, indices, 4, 6, VertexDescriptor::POSITION);
    std::shared_ptr<Mesh> mesh2 = MeshCreator::CreateMesh(vertices2, indices, 4, 6, VertexDescriptor::POSITION);
    mesh.get()->properties["factor"] = 0.5f;
    mesh2.get()->properties["factor"] = 1.0f;

    mesh.get()->properties["color"] = glm::vec4(0.0, 0.2, 0.0, 1.0);
    mesh2.get()->properties["color"] = glm::vec4(0.0, 0.0, 0.2, 1.0);
    */

  //  std::shared_ptr<Mesh> cube1 = MeshCreator::CreateMesh(data::UnitHalfCubeVertices, data::UnitCubeIndices, 8, 36, VertexDescriptor::POSITION);
  //  std::shared_ptr<Mesh> cube2 = MeshCreator::CreateMesh(data::UnitHalfCubeVertices, data::UnitCubeIndices, 8, 36, VertexDescriptor::POSITION);
    
  //  cube1.get()->properties["color"] = glm::vec4(0.0, 0.2, 0.0, 1.0);
  //  cube2.get()->properties["color"] = glm::vec4(0.2, 0.0, 0.0, 1.0);

  //  cube1.get()->SetPosition(glm::vec3(0.5f, 0.5f, 0.0f));
  //  cube2.get()->SetPosition(glm::vec3(-0.5f, -0.5f, 0.0f));

  //  Scene::GetInstance()->AddMesh(cube1);
   // Scene::GetInstance()->AddMesh(cube2);
    //Scene::GetInstance()->AddMesh(mesh2);

    std::vector<float> pun = data::GetCubeVertices();
    std::vector<int> indices(36, 0);
    for (int i = 0; i < 36; i++)
    {
        indices.data()[i] = i;
    }

    //std::shared_ptr<Mesh> cube = MeshCreator::CreateMesh();
    //cube.get()->properties["color"] = glm::vec4(0.0, 0.3, 0.0, 1.0);
    //cube.get()->SetPosition(glm::vec3(0.5f, 0.5f, 0.0f));

    std::shared_ptr<BaseMaterial> material = MaterialCreator::Builder().get()
    ->Type(ObjectType::VERTEX_BASE)
//    ->AddTexture(TextureType::ALBEDO, "resources/textures/texture1.jpg")
    //->AddTexture(TextureType::ALBEDO, data::GetSampleGradientTexture(1024), 1024, 1024)
    ->AddTexture(TextureType::ALBEDO, "resources/textures/texture1.jpg")
    ->ReceiveShadow()
    ->Build();

    std::shared_ptr<Geometry> geometry = GeometryCreator::Builder().get()
    ->AddMesh(pun.data(), indices.data(), 36, 36, VertexDescriptor::VERTEX_BASE)
    ->SetMaterial(material)
    ->SetPosition(glm::vec3(1.0, 0.0, 0.0))
    ->AddProperties("u_color", glm::vec4(0.0, 0.3, 0.0, 1.0))
    ->Build();

    std::vector<VertexBase> vertexBases;
    ObjLoader::LoadVertexBase("resources/objs/sphere.obj", vertexBases);

    std::vector<int> vertexIndices;
    vertexIndices.resize(vertexBases.size());
    std::iota(vertexIndices.begin(), vertexIndices.end(), 0);

        //for (size_t i = 0; ;i++)
        //creator2->AddMesh(attrib);
        /*
        GeometryCreator::Builder().get()->AddMesh(
            attrib.GetVertices().data(), 
            shapes[0].mesh.indices.data(),

            );
            */

    std::shared_ptr<Geometry> sphereGeo =  GeometryCreator::Builder().get()->AddMesh((float *)vertexBases.data(), vertexIndices.data(), vertexIndices.size(), vertexIndices.size(), VertexDescriptor::VERTEX_BASE)
    ->SetMaterial(material)
    ->SetPosition(glm::vec3(0.0, 1.0, 0.0))
    ->Build();


    std::vector<VertexBase> planeVerts;
    ObjLoader::LoadVertexBase("resources/objs/plane.obj", planeVerts);
    std::vector<int> planeIndices;
    planeIndices.resize(planeVerts.size());
    std::iota(planeIndices.begin(), planeIndices.end(), 0);

    std::shared_ptr<Geometry> planeGeo = GeometryCreator::Builder().get()->AddMesh((float*)planeVerts.data(), planeIndices.data(), planeVerts.size(), planeIndices.size(), VertexDescriptor::VERTEX_BASE)
    ->SetMaterial(material)
    ->SetPosition(glm::vec3(0, 0, 0))
    ->SetScale(glm::vec3(2))
    ->Build();

    //Scene::GetInstance()->AddGeometry(geometry);
    //Scene::GetInstance()->AddGeometry(geometry2);
    Scene::GetInstance()->AddGeometry(sphereGeo);
    Scene::GetInstance()->AddGeometry(planeGeo);

    //Camera::Get()->SetInitPosition(glm::vec3(0.0f, 5.0f, 5.0f));
    //Camera::Get()->SetInitPosition(glm::vec3(-6.0f, 3.22f, -1.69f));

    Camera::Get()->SetInitPosition(glm::vec3(.0f, 5.0f, 20.0f));

    //Camera::Get()->SetInitPosition(glm::vec3(278.0f, 278.0f, 800.0f));
    RaySceneLoader::Init();

    DirectionalLight light;
    light.SetDirection(glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)));
    light.SetColor(glm::vec3(0.2f, 0.0f, 0.0f));

    Scene::GetInstance()->AddDirectionalLight(light);
}