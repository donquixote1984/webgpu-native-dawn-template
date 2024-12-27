#pragma once
#include "Hitable.h"
#include <string>
#include <vector>

struct BVHNodeUniform;
class BVH
{
public:
    std::string name;
    int left = -1;
    int right = -1;
    int hier;
    bool isLeaf = false;
    Hitable hitable;
    std::vector<Hitable> objs;
    AABB aabb;

    BVHNodeUniform ToBVHNodeUniform();
};