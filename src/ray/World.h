#pragma once
#include <vector>
#include "Hitable.h"
#include "BVH.h"

#include <iostream>
struct BVHUniform;
struct HitableListUniform;
class World
{
private:
    const int AXIS_X = 0;
    const int AXIS_Y = 1;
    const int AXIS_Z = 2;

    std::vector<Hitable> hitables;
    std::shared_ptr<BVH> root = std::make_shared<BVH>();
    std::vector<std::shared_ptr<BVH>> bvhList;
public:
    World(std::vector<Hitable> hitables): hitables(hitables)
    {
        root.get()->hier = 0;
        root.get()->isLeaf = false;
        root.get()->name = "root";
        root.get()->objs = hitables;
        InitBVH();
    }

    void InitBVH()
    {
       
        ConstructBVH();
        BindAABB(root);
        OutputBVH(root);
    }

    float GetMinComponent(AABB aabb, int axis)
    {
        if (axis == AXIS_X) {
            return aabb.min.x;
        }

        if (axis == AXIS_Y) {
            return aabb.min.y;
        }

        if (axis == AXIS_Z) {
            return aabb.min.z;
        }
    }



    int ConstructBVH()
    {
        //bvh.name = name;
        int stack[100];
        int stackIndex = 0;
        int currentBVHDictIndex = 1;
        stack[0] = 0;
        bvhList.push_back(root);
        while(stackIndex >= 0)
        {
            int currentBVHIndex = stack[stackIndex];
            BVH* bvh = bvhList[currentBVHIndex].get();
            int axis_x = bvh->hier %3;
            if (bvh->objs.size() <= 1)
            {
                bvh->isLeaf = true;
                bvh->hitable = bvh->objs[0];
                bvh->aabb = bvh->objs[0].GetAABB();
                stackIndex -= 1;
                continue;
            }

            std::sort(std::begin(bvh->objs), std::end(bvh->objs), [&](const Hitable & a, const Hitable & b){
                return GetMinComponent(a.GetAABB(), axis_x) < GetMinComponent(b.GetAABB(), axis_x);
            });

            int mid = bvh->objs.size() / 2;
            std::shared_ptr<BVH> left = std::make_shared<BVH>();
            std::shared_ptr<BVH> right = std::make_shared<BVH>();
            left.get()->isLeaf = false;
            right.get()->isLeaf = false;
            std::vector<Hitable> leftV;
            std::vector<Hitable> rightV;
            leftV.assign(bvh->objs.begin(), bvh->objs.begin() + mid);
            rightV.assign(bvh->objs.begin() + mid, bvh->objs.end());

            left.get() ->objs = leftV;
            left.get()->hier = bvh->hier + 1;
            left.get()->name = bvh->name + "_left";
            
            right.get()->objs = rightV;
            right.get()->hier = bvh->hier + 1;
            right.get()->name = bvh->name + "_right";

            bvh->right = currentBVHDictIndex;
            bvhList.push_back(right);
            currentBVHDictIndex += 1;

            bvh->left = currentBVHDictIndex;
            bvhList.push_back(left);
            currentBVHDictIndex+= 1;

            stack[stackIndex] = bvh->left;
            stack[++stackIndex] = bvh->right;
        }
    }

    void BindAABB(std::shared_ptr<BVH> _bvh)
    {
        BVH * bvh = _bvh.get();
        if (bvh->isLeaf) {
            bvh->aabb = bvh->hitable.GetAABB();
            return;
        }
        std::shared_ptr<BVH> left = bvhList[bvh->left];
        std::shared_ptr<BVH> right = bvhList[bvh->right];
        BindAABB(left);
        BindAABB(right);

        bvh->aabb = left.get()->aabb.Merge(right.get()->aabb);
    }

    void OutputBVH(std::shared_ptr<BVH> bvh)
    {
        std::cout << bvh.get()->name <<" "<<bvh.get()->aabb.ToString() << std::endl;
        if (bvh.get()->left > 0) 
        {
            std::shared_ptr<BVH> left = bvhList[bvh.get()->left];
            OutputBVH(left);
        }
        if (bvh.get()->right > 0) 
        {

            std::shared_ptr<BVH> right = bvhList[bvh.get()->right];
            OutputBVH(right);
        }
    }

    HitableListUniform GetHitableListUniform();
    BVHUniform ToBVHListUniform();
};