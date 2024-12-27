#pragma once
#include "Hitable.h"
#include <vector>
#include <memory>
#include "World.h"
#include "../uniforms/BVHUniform.h"
#include "../uniforms/RayHitableUniform.h"
#include "../textures/DiskTextureObject.h"
#include "../canvas/RayCanvasSimple.h"
class RaySceneLoader
{
public:
    static void InitTest()
    {
        std::vector<Hitable> hitables;


        
        HitableMaterial lambert_earth = HitableMaterial::CreateLambert(glm::vec3(0.8f, 0.8f, 0.0f)); 
        HitableMaterial lambert_mat1 = HitableMaterial::CreateLambert(glm::vec3(0.1, 0.2, 0.5)); 
        HitableMaterial metal_mat1 = HitableMaterial::CreateMetal(glm::vec3(0.5, 0.5, 0.8));
        HitableMaterial metal_mat2= HitableMaterial::CreateMetal(glm::vec3(0.8, 0.6, 0.2));
        HitableMaterial bubble_mat= HitableMaterial::CreateDiel(1.0f/1.5f);
        HitableMaterial diel_mat = HitableMaterial::CreateDiel(1.5f);
        HitableMaterial lambert_color1 = HitableMaterial::CreateLambert(glm::vec3(0.1, 0.2, 0.4));
        HitableMaterial lambert_color2 = HitableMaterial::CreateLambert(glm::vec3(0.6, 0.2, 0.1));
        HitableMaterial lambert_color3 = HitableMaterial::CreateLambert(glm::vec3(0.5, 0.2, 0.6));
        HitableMaterial lambert_color4 = HitableMaterial::CreateLambert(glm::vec3(0.8, 0.5, 0.4));

        HitableMaterial  metal_color1 = HitableMaterial::CreateMetal(glm::vec3(0.6, 0.2, 0.6));
        HitableMaterial  metal_color2 = HitableMaterial::CreateMetal(glm::vec3(0.1, 0.1, 0.3));
        HitableMaterial  metal_color3 = HitableMaterial::CreateMetal(glm::vec3(0.4, 0.4, 0.2));

        HitableMaterial checker_mat = HitableMaterial::CreateChecker(glm::vec3(0.5, 0.0, 0.0), 10.0f);

        HitableMaterial texture_mat = HitableMaterial::CreateTextureMaterial();
        HitableMaterial emissive_mat1 = HitableMaterial::CreateEmissive(glm::vec3(4.0, 4.0, 4.0));
        HitableMaterial emissive_mat2 = HitableMaterial::CreateEmissive(glm::vec3(4.0, 0.0, 4.0));

/*
        Sphere sphere1 = Sphere(glm::vec3(1,1,1), .5f);
        sphere1.SetMaterial(lambert_mat1);

        Sphere sphere2 = Sphere(glm::vec3(1,1,-1), .5f);
        sphere2.SetMaterial(lambert_color1);

        Sphere sphere3 = Sphere(glm::vec3(-1,1,-1), .5f);
        sphere3.SetMaterial(metal_mat1);

        Sphere sphere4 = Sphere(glm::vec3(-1,1,1), .5f);
        sphere4.SetMaterial(metal_mat2);

        Sphere sphere5 = Sphere(glm::vec3(1,-1,1), .5f);
        sphere5.SetMaterial(lambert_mat1);

        Sphere sphere6 = Sphere(glm::vec3(1,-1,-1), .5f);
        sphere6.SetMaterial(lambert_color1);

        Sphere sphere7 = Sphere(glm::vec3(-1,-1,-1), .5f);
        sphere7.SetMaterial(metal_mat1);

        Sphere sphere8 = Sphere(glm::vec3(-1,-1,1), .5f);
        sphere8.SetMaterial(metal_mat2);
        */

/*
        sphere1.SetIndex(0);
        hitables.push_back(sphere1);
        sphere2.SetIndex(1);
        hitables.push_back(sphere2);
        sphere3.SetIndex(2);
        hitables.push_back(sphere3);
        sphere4.SetIndex(3);
        hitables.push_back(sphere4);
        sphere5.SetIndex(4);
        hitables.push_back(sphere5);
        sphere6.SetIndex(5);
        hitables.push_back(sphere6);
        sphere7.SetIndex(6);
        hitables.push_back(sphere7);
        sphere8.SetIndex(7);
        hitables.push_back(sphere8);
        */
        Sphere earth = Sphere(glm::vec3(0, -100.5f, -1.0f), 100.0f); 
        earth.SetMaterial(lambert_earth);
        earth.SetIndex();
        hitables.push_back(earth);

        Sphere sphere1 = Sphere(glm::vec3(0, 0, -1.0f), 0.5f); 
        sphere1.SetMaterial(texture_mat);
        sphere1.SetIndex();
        hitables.push_back(sphere1);

        Sphere sphere_metal1 = Sphere(glm::vec3(-1.0,0.0, -1.0), 0.5);
        sphere_metal1.SetMaterial(lambert_mat1);
        sphere_metal1.SetIndex();
        hitables.push_back(sphere_metal1);


        Sphere sphere_diel1 = Sphere(glm::vec3(1.0f, 0.0f, -1.0f), 0.5);
        sphere_diel1.SetMaterial(diel_mat);
        sphere_diel1.SetIndex();
        hitables.push_back(sphere_diel1);

        Sphere sphere_diel2 = Sphere(glm::vec3(1.0f, 0.0f, -1.0f), 0.4);
        sphere_diel2.SetMaterial(bubble_mat);
        sphere_diel2.SetIndex();
        hitables.push_back(sphere_diel2);

        Sphere sphere_lsmall1 = Sphere(glm::vec3(-0.5,-0.1, 0.9), 0.3);
        sphere_lsmall1.SetMaterial(lambert_color1);
        sphere_lsmall1.SetIndex();
        hitables.push_back(sphere_lsmall1);

        Sphere sphere_lsmall2 = Sphere(glm::vec3(0.2,-0.0f, 1.0), 0.3f);
        sphere_lsmall2.SetMaterial(lambert_color1);
        sphere_lsmall2.SetIndex();
        hitables.push_back(sphere_lsmall2);

        Sphere sphere_lsmall3 = Sphere(glm::vec3(0.5f,-0.2, 0.2), 0.2f);
        sphere_lsmall3.SetMaterial(checker_mat);
        sphere_lsmall3.SetIndex();
        hitables.push_back(sphere_lsmall3);

        Sphere sphere_msmall1 = Sphere(glm::vec3(-1.5f, -0.0f, 0.5f), 0.4f);
        sphere_msmall1.SetMaterial(metal_color1);
        sphere_msmall1.SetIndex();
        
        hitables.push_back(sphere_msmall1);

        Sphere sphere_msmall2 = Sphere(glm::vec3(0.8f, -0.2f, 1.2f), 0.2f);
        sphere_msmall2.SetMaterial(metal_color2);
        sphere_msmall2.SetIndex();
        hitables.push_back(sphere_msmall2);


        Sphere sphere_msmall3 = Sphere(glm::vec3(1.0f, -0.1f, 0.3), 0.3f);
        sphere_msmall3.SetMaterial(metal_color3);
        sphere_msmall3.SetIndex();
        hitables.push_back(sphere_msmall3);


        Quad quad = Quad(glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(2, 0, 0), glm::vec3(0, 0, 2));
        quad.SetMaterial(emissive_mat1);
        quad.SetIndex();
        hitables.push_back(quad);
        
        //Quad quad = Quad(glm::vec3(-2,-2, 0), glm::vec3(4, 0, 0), glm::vec3(0, 4, 0));
        //quad.SetMaterial(lambert_color3);
        //quad.SetIndex();
        //hitables.push_back(quad);

        World world(hitables);
        //HitableListUniformBuffer::WriteValue();
        //BVHUniformBuffer::WriteValue();

        UniformBuffer *hitableUniformBuffer = HitableListUniformBuffer::Get();
        HitableListUniform uniform = world.GetHitableListUniform();
        WGPUContext::queue.writeBuffer(hitableUniformBuffer->GetBuffer(), 0, &uniform, sizeof(uniform));

        BVHUniform bvhuniform = world.ToBVHListUniform();
        UniformBuffer *bvhUniformBuffer= BVHUniformBuffer::Get();
        WGPUContext::queue.writeBuffer(bvhUniformBuffer->GetBuffer(), 0, &bvhuniform, sizeof(bvhuniform));


        InitTextures();
    }

    static void InitTestBox()
    {
        std::vector<Hitable> hitables;
        HitableMaterial r = HitableMaterial::CreateLambert(glm::vec3(.65, .05, .05));
         // box1
        Box box = Box(glm::vec3(-1, -1, -1), glm::vec3(2,2,2), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
        box.SetMaterial(r);
        box.AddToHitables(hitables);
        World world(hitables);
        //HitableListUniformBuffer::WriteValue();
        //BVHUniformBuffer::WriteValue();

        UniformBuffer *hitableUniformBuffer = HitableListUniformBuffer::Get();
        HitableListUniform uniform = world.GetHitableListUniform();
        WGPUContext::queue.writeBuffer(hitableUniformBuffer->GetBuffer(), 0, &uniform, sizeof(uniform));

        BVHUniform bvhuniform = world.ToBVHListUniform();
        UniformBuffer *bvhUniformBuffer= BVHUniformBuffer::Get();
        WGPUContext::queue.writeBuffer(bvhUniformBuffer->GetBuffer(), 0, &bvhuniform, sizeof(bvhuniform));

        InitTextures();

    }
    static void InitCornellBox()
    {
        std::vector<Hitable> hitables;
        HitableMaterial g = HitableMaterial::CreateLambert(glm::vec3(.12, .45, .15)); 
        HitableMaterial r = HitableMaterial::CreateLambert(glm::vec3(.65, .05, .05)); 
        HitableMaterial w = HitableMaterial::CreateLambert(glm::vec3(.73, .73, .73)); 
        HitableMaterial light = HitableMaterial::CreateEmissive(glm::vec3(15, 15, 15));

        //left 
        Quad quad1 = Quad(glm::vec3(-5, -5, -5),  glm::vec3(0, 10, 0), glm::vec3(0, 0, 10));
        quad1.SetMaterial(g);
        quad1.SetIndex();
        quad1.name = "left";
        hitables.push_back(quad1);


        // right
        Quad quad2 = Quad(glm::vec3(5, -5, 5),  glm::vec3(0, 10, 0), glm::vec3(0, 0, -10));
        quad2.SetMaterial(r);
        quad2.SetIndex();
        quad2.name = "right";
        hitables.push_back(quad2);

        //light
        Quad quad3 = Quad(glm::vec3(-4, 4.9, -3), glm::vec3(6,0,0), glm::vec3(0,0,6));
        quad3.SetMaterial(light);
        quad3.SetIndex();
        quad3.name = "light";
        hitables.push_back(quad3);

        //back
        Quad quad4 = Quad(glm::vec3(-5, -5, -5), glm::vec3(10,0,0), glm::vec3(0,10,0));
        quad4.SetMaterial(w);
        quad4.SetIndex();
        quad4.name = "back";
        hitables.push_back(quad4);

        //front
        //Quad quad7 = Quad(glm::vec3(-50, -50, 20), glm::vec3(100,0,0), glm::vec3(0,100,0));
        //quad7.SetMaterial(w);
        //quad7.SetIndex();
        //hitables.push_back(quad7);

        // top
        Quad quad5 = Quad(glm::vec3(-5, 5, 5), glm::vec3(0,0,-10), glm::vec3(10,0,0));
        quad5.SetMaterial(w);
        quad5.SetIndex();
        quad5.name = "top";
        hitables.push_back(quad5);

        // bottom
        Quad quad6 = Quad(glm::vec3(-5, -5, 5), glm::vec3(10,0,0), glm::vec3(0,0,-10));
        quad6.SetMaterial(w);
        quad6.SetIndex();
        quad6.name = "bottom";
        hitables.push_back(quad6);

      

/*
        Quad quad4 = Quad(glm::vec3(0, 0, 0), glm::vec3(555, 0, 0), glm::vec3(0, 0, 555));
        quad1.SetMaterial(w);
        quad1.SetIndex();
        hitables.push_back(quad4);

        Quad quad5 = Quad(glm::vec3(555,555,555), glm::vec3(-555, 0, 0), glm::vec3(0, 0, -555));
        quad1.SetMaterial(w);
        quad1.SetIndex();
        hitables.push_back(quad5);

        Quad quad6 = Quad(glm::vec3(0,0,555), glm::vec3(555, 0, 0), glm::vec3(0, 555, 0));
        quad1.SetMaterial(w);
        quad1.SetIndex();
        hitables.push_back(quad6);
        */

        Box box = Box(glm::vec3(-2, -5, -1), glm::vec3(2,5,2), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
        box.SetMaterial(w);
        box.AddToHitables(hitables);

        Box box2 = Box(glm::vec3(-1, -5, 1), glm::vec3(3,3,3), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
        box2.SetMaterial(w);
        box2.AddToHitables(hitables);

        World world(hitables);
        //HitableListUniformBuffer::WriteValue();
        //BVHUniformBuffer::WriteValue();

        UniformBuffer *hitableUniformBuffer = HitableListUniformBuffer::Get();
        HitableListUniform uniform = world.GetHitableListUniform();
        WGPUContext::queue.writeBuffer(hitableUniformBuffer->GetBuffer(), 0, &uniform, sizeof(uniform));

        BVHUniform bvhuniform = world.ToBVHListUniform();
        UniformBuffer *bvhUniformBuffer= BVHUniformBuffer::Get();
        WGPUContext::queue.writeBuffer(bvhUniformBuffer->GetBuffer(), 0, &bvhuniform, sizeof(bvhuniform));

        InitTextures();

    }
    static void Init()
    {
        InitCornellBox();
        //InitTestBox();

    }

    static void InitTextures()
    {

        RayCanvasSimple::Get()->AddTexture(std::make_shared<DiskTextureObject>("resources/textures/noise/bluenoise2.png"));
        RayCanvasSimple::Get()->AddTexture(std::make_shared<DiskTextureObject>("resources/textures/raytracing-sample/earthmap.jpg"));

    }
};