#include "BVH.h"
#include "../uniforms/BVHUniform.h"
BVHNodeUniform BVH::ToBVHNodeUniform()
{
    BVHNodeUniform uniform;
    uniform.aabb = aabb;
    uniform.hitable = hitable.GetIndex();
    uniform.isLeaf = isLeaf;
    uniform.left = left;
    uniform.right = right;
    return uniform;
}