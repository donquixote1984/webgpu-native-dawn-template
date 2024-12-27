#pragma once
#include <vector>
#include "AABB.h"


class HitableMaterialUniform;
class HitablePropertiesUniform;
class HitableUniform;

enum class MaterialType 
{
    LAMBERT = 101,
    METAL = 202,
    DIEL = 303,
    CHECKER = 404,
    TEXTURED = 505,
    EMISSIVE = 606,
};

enum class PrimitiveType
{
    SPHERE = 0,
    CUBE =1,
    QUAD = 2,
    BOX = 3,
};

struct HitableMaterial
{
    MaterialType type; // 0 lambert, 1 material, 2 diel
    float refractIndex = 0.0f;
    glm::vec4 color = glm::vec4(0.0f, 0.0f,0.0f, 1.0f);
    float factor = 0.0f;

    static HitableMaterial CreateLambert(glm::vec3 color)
    {
        HitableMaterial mat = {};
        mat.type= MaterialType::LAMBERT;
        mat.color = glm::vec4(color, 1.0f);
        return mat;
        //return HitableMaterial(LAMB_MAT, 0, color);
    }

    static HitableMaterial CreateMetal(glm::vec3 color)
    {
        HitableMaterial mat = {};
        mat.type= MaterialType::METAL;
        mat.color = glm::vec4(color, 1.0f);
        return mat;
        //return HitableMaterial(METAL_MAT, 0, color);
    }
    static HitableMaterial CreateChecker(glm::vec3 color, float factor)
    {
        HitableMaterial mat = {};
        mat.type = MaterialType::CHECKER;
        mat.color = glm::vec4(color, 1.0f);
        mat.factor = factor;
        return mat;
    }

    static HitableMaterial CreateDiel(float rIndex)
    {
        HitableMaterial mat = {};
        mat.type= MaterialType::DIEL;
        mat.refractIndex = rIndex;
        mat.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        return mat;
        //return HitableMaterial(DIEL_MAT, rIndex, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    static HitableMaterial CreateTextureMaterial()
    {
        HitableMaterial mat = {};
        mat.type = MaterialType::TEXTURED;
        return mat;
    }

    static HitableMaterial CreateEmissive(glm::vec3 color)
    {
        HitableMaterial mat = {};
        mat.type = MaterialType::EMISSIVE;
        mat.color = glm::vec4(color, 1.0f);
        return mat;
    }


    HitableMaterialUniform ToHitableMaterialUniform();

};

struct HitableProperties
{
    float radius;
    glm::vec4 mbTowards;
    glm::vec4 center;

    glm::vec4 min;
    glm::vec4 max;

    glm::vec4 normal;

    glm::vec4 u;
    glm::vec4 v;

    glm::vec4 extra;

    HitablePropertiesUniform ToHitablePropertiesUniform();
};

class Hitable
{
protected:
    int index;
    PrimitiveType type; //  sphere,  cube
    AABB aabb;
    
    HitableMaterial material;
    HitableProperties properties = {};
    
public:
    std::string name;
    Hitable() {}
    static int _index;
    void SetMaterial(HitableMaterial m)
    {
        material = m;
    }
    void SetIndex(int i){
        index = i;
    }
    void SetIndex()
    {
        index = Hitable::_index;
        Hitable::_index +=1;
    }
    const int GetIndex() const 
    {
        return index;
    }
    const AABB & GetAABB() const
    {
        return aabb;
    }
    
    HitableUniform ToHitableUniform();

};

class Sphere: public Hitable
{
private:
    glm::vec3 center;
    float radius;
public:
    Sphere(glm::vec3 center, float radius): center(center), radius(radius)
    {
        type = PrimitiveType::SPHERE;
        // aabb
        aabb.min = glm::vec4(glm::vec3(center) - glm::vec3(radius), 1.0f);
        aabb.max = glm::vec4(glm::vec3(center) + glm::vec3(radius), 1.0f);

        properties.center = glm::vec4(center, 1.0f);
        properties.radius = radius;
    }
};

class Cube: public Hitable
{

};

class Quad: public Hitable
{
private:
    glm::vec3 q;
    glm::vec3 u, v;
    glm::vec3 w;
    glm::vec3 normal;
    float D;
public: 
    Quad(){}
    Quad(const glm::vec3 &q, const glm::vec3 &u, const glm::vec3 & v): q(q), u(u), v(v)
    {
        auto n = glm::cross(u, v);
        normal = glm::normalize(n);
        D = dot(normal, q);
        w = n / dot(n, n);

        type = PrimitiveType::QUAD;
        AABB aabb1;
        aabb1.min = glm::vec4(q, 1.0);
        aabb1.max = glm::vec4(q + u + v, 1.0);

        AABB aabb2;
        aabb2.min = glm::vec4(q + u, 1.0);
        aabb2.max = glm::vec4(q + v, 1.0);

        aabb = aabb1.Merge(aabb2);
        aabb.PadToMinimum();
        CorrectAABB();


        properties.normal = glm::vec4(normal, 1.0);
        properties.center = glm::vec4(q, 1.0);

        properties.u = glm::vec4(u, 1.0f);
        properties.v = glm::vec4(v, 1.0f);

        properties.extra = glm::vec4(w, D);
    }

    void CorrectAABB()
    {
        if (aabb.min.x < aabb.max.x && aabb.min.y < aabb.max.y && aabb.min.z < aabb.max.z) {
            // aabb correct
            return;
        }
        
        glm::vec3 diff = glm::vec3(aabb.min - aabb.max);

        if (aabb.min.x > aabb.max.x)
        {
            aabb.min.x -= diff.x;
            aabb.max.x += diff.x;
        }

        if (aabb.min.y > aabb.max.y) {
            aabb.min.y -= diff.y;
            aabb.max.y += diff.y;
        }

        if (aabb.min.z > aabb.max.z) 
        {
            aabb.min.z -= diff.z;
            aabb.max.z += diff.z;
        }
    }
};


class Box
{
    /***
     * 
     *  float sdBox( vec3 p, vec3 b )
        {
            vec3 q = abs(p) - b;
            return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
        }
     * 
    */
private:
    glm::vec3 min;
    glm::vec3 bounds;
    Quad quads[6];
public:
    Box(const glm::vec3 &min, const glm::vec3 &bounds, const glm::vec3 &up, const glm::vec3 & right)
    {
        //type = PrimitiveType::BOX;

        //front


        glm::vec3 lookAt = glm::normalize(glm::cross(up, right));
        glm::vec3 frontMin = min + -lookAt * bounds.z;

        glm::vec3 max = min + right * bounds.x + up * bounds.y -lookAt * bounds.z;


        quads[0] = Quad(min, up * bounds.y, right * bounds.x); // back
        quads[0].SetIndex();
        quads[1] = Quad(frontMin, up * bounds.y, right * bounds.x); // front
        quads[1].SetIndex();
        quads[2] = Quad(min, up * bounds.y, -lookAt * bounds.z); // left,
        quads[2].SetIndex();
        quads[3] = Quad(max, lookAt * bounds.z, -up * bounds.y); // right;
        quads[3].SetIndex();

        quads[4] = Quad(max, lookAt * bounds.z, -right * bounds.x); // top
        quads[4].SetIndex();

        quads[5] = Quad(min, right * bounds.x, -lookAt * bounds.z); // bottom
        quads[5].SetIndex();

    }
    void SetMaterial(HitableMaterial m)  {
        for (int i = 0; i < 6; i++)
        {
            quads[i].SetMaterial(m);
        }
    }

    void AddToHitables(std::vector<Hitable> &hitables)
    {
        for (int i = 0; i < 6; i++)
        {
            hitables.push_back(quads[i]);
        }
    }
};