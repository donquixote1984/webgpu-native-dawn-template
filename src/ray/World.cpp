#include "World.h"
#include "../uniforms/BVHUniform.h"
#include "../uniforms/RayHitableUniform.h"

BVHUniform World::ToBVHListUniform()
{
    BVHUniform uniform;
    std::vector<BVHNodeUniform> uniformList(bvhList.size());
    std::transform(bvhList.begin(), bvhList.end(),uniformList.begin(), [](std::shared_ptr<BVH> bvh){
        return bvh.get()->ToBVHNodeUniform();
    });
    for (int i = 0; i < uniformList.size(); i++)
    {
        uniform.bvhList[i] = uniformList[i];
    }
    uniform.root = root.get()->ToBVHNodeUniform();
    return uniform;
}

HitableListUniform World::GetHitableListUniform()
{
    HitableListUniform uniform;
    uniform.count = hitables.size();
    std::vector<HitableUniform> uniformList(hitables.size());
    std::transform(hitables.begin(), hitables.end(), uniformList.begin(), [](Hitable &hitable){
        return hitable.ToHitableUniform();
    });

    for (int i = 0; i < uniformList.size(); i++)
    {
        uniform.hitableList[i] = uniformList[i];
    }
    return uniform;
}