/**
1. aabb 检测， 
最大的tmin和最小的tmax比较， 可以从2D图片看出collison对应的t位置和non-collision对应的t位置比对， 从而推广到3d https://izzofinal.wordpress.com/2012/11/09/ray-vs-box-round-1/

2. 为什么bvh可以加速

组织之后的object list经过空间分割之后， 通过每次递归的局部aabb做提前判断， 如果当前的aabb没有hit， 那么它内部的所有aabb都不需要在检测了
*/

fn merge_aabb(bb1:AABB, bb2:AABB)->AABB
{
    var aabb: AABB;
    aabb.min.x = min(bb1.min.x, bb2.min.x);
    aabb.min.y = min(bb1.min.y, bb2.min.y);
    aabb.min.z = min(bb1.min.z, bb2.min.z);

    aabb.max.x = min(bb1.max.x, bb2.max.x);
    aabb.max.y = min(bb1.max.y, bb2.max.y);
    aabb.max.z = min(bb1.max.z, bb2.max.z);

    return aabb;
}



fn check_ray_hit_on_aabb(r: Ray, aabb: AABB)->bool
{
    var current_ray = r;
    var dir_frac: vec3f;
    if (r.dir.x == 0)
    {
        dir_frac.x = MAX_INF;
    } else {
        dir_frac.x = 1.0f / r.dir.x;
    }

    if (r.dir.y == 0)
    {
        dir_frac.y = MAX_INF;
    } else {
        dir_frac.y = 1.0f / r.dir.y;
    }

    if (r.dir.z == 0)
    {
        dir_frac.z = MAX_INF;
    } else {
        dir_frac.z = 1.0f / r.dir.z;
    }

    var t1: f32 = (aabb.min.x - current_ray.orig.x) * dir_frac.x;  
    var t2: f32 = (aabb.max.x - current_ray.orig.x) * dir_frac.x;

    var t3: f32 = (aabb.min.y - current_ray.orig.y) * dir_frac.y;
    var t4: f32 = (aabb.max.y - current_ray.orig.y) * dir_frac.y;

    var t5: f32 = (aabb.min.z - current_ray.orig.z) * dir_frac.z;
    var t6: f32 = (aabb.max.z - current_ray.orig.z) * dir_frac.z;

    var tmin: f32 = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    var tmax: f32 = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    if (tmax < 0)
    {
        return false;
    }
    if (tmin > tmax)
    {
        return false;
    }
    return true;
}

fn check_ray_hit_on_aabb_tmin_tmax(r: Ray, aabb: AABB, _tmin: f32, _tmax:f32)->bool 
{
     var current_ray = r;
    var dir_frac: vec3f;
    if (r.dir.x == 0)
    {
        dir_frac.x = MAX_INF;
    } else {
        dir_frac.x = 1.0f / r.dir.x;
    }

    if (r.dir.y == 0)
    {
        dir_frac.y = MAX_INF;
    } else {
        dir_frac.y = 1.0f / r.dir.y;
    }

    if (r.dir.z == 0)
    {
        dir_frac.z = MAX_INF;
    } else {
        dir_frac.z = 1.0f / r.dir.z;
    }

    var t1: f32 = (aabb.min.x - current_ray.orig.x) * dir_frac.x;  
    //t1 = max(t1, _tmin);
    var t2: f32 = (aabb.max.x - current_ray.orig.x) * dir_frac.x;
    //t2 = min(t2, _tmax);

    var t3: f32 = (aabb.min.y - current_ray.orig.y) * dir_frac.y;
    //t3 = max(t3, _tmin);
    var t4: f32 = (aabb.max.y - current_ray.orig.y) * dir_frac.y;
    //t4 = min(t4, _tmax);

    var t5: f32 = (aabb.min.z - current_ray.orig.z) * dir_frac.z;
    //t5 = max(t5, _tmin);
    var t6: f32 = (aabb.max.z - current_ray.orig.z) * dir_frac.z;
    //t6 = min(t6, _tmax);

    var tmin: f32 = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    var tmax: f32 = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));
    tmin = max(tmin, _tmin);
    tmax = min(tmax, _tmax);

    if (tmax < 0)
    {
        return false;
    }
    if (tmin > tmax)
    {
        return false;
    }
    return true;
}



fn get_aabb_component_min(hitable: Hitable, axis: i32) -> f32
{
    if (axis == AXIS_X) 
    {
        return hitable.aabb.min.x;
    }

    if (axis == AXIS_Y)
    {
        return hitable.aabb.min.y;
    }

    if (axis == AXIS_Z)
    {
        return hitable.aabb.min.z;
    }

    return hitable.aabb.min.x;
}

fn array_slice (bvh_objs: array<Hitable, GEO_NUM>, _from: i32, _to: i32)-> array<Hitable, GEO_NUM>
{
    var result_objs: array<Hitable, GEO_NUM>;
    for (var i : i32 = 0; i < _to - _from; i++)
    {
        result_objs[i] = bvh_objs[i + _from];
    }

    return result_objs;
}

fn sort_bvh_array(bvh_objs: array<Hitable, GEO_NUM>, array_num: i32, axis: i32) -> array<Hitable, GEO_NUM>
{
    var sortted_bvh_objs: array<Hitable, GEO_NUM> = bvh_objs;

    for (var i: i32 = 0; i < array_num; i++)
    {
        for (var j: i32 = 0; j < array_num-i-1; j++)
        {
            if (get_aabb_component_min(sortted_bvh_objs[j], axis) > get_aabb_component_min(sortted_bvh_objs[j+1], axis))
            {
                let tmp = sortted_bvh_objs[j];
                sortted_bvh_objs[j] = sortted_bvh_objs[j+1];
                sortted_bvh_objs[j+1] = tmp;
            }
        }
    }
   
    return sortted_bvh_objs;
}



/*
fn init_bvh_world(world: array<Hitable, GEO_NUM>)->BVHContainer
{

    
    var bvh_dict_arr: array<BVH, MAX_BVH_DICT_SIZE>;
    var current_sort_axis = AXIS_X;
    var stack: array<i32, MAX_BVH_DICT_SIZE>;
    var rootBVH: BVH;

    rootBVH.isLeaf = false;
    rootBVH.geos = world;
    rootBVH.hier = 0;
    rootBVH.geoNum = GEO_NUM;

    bvh_dict_arr[0] = rootBVH;
    stack[0] = 0;
    var stackIndex:i32 = 0;
    var currentBVHDictIndex: i32 = 1;

    var loopLimit: i32 = 30;
    var i: i32 = 0;
    var sortedObjs: array<Hitable, GEO_NUM>;
    while(stackIndex >= 10)
    {
        if (stackIndex > loopLimit) {
            break;
        }
        var currentBVHIndex: i32 = stack[stackIndex];
        var bvh: BVH = bvh_dict_arr[currentBVHIndex];
        var axis_x: i32 = bvh.hier % 3;

        if (bvh.geoNum <=1) {
            bvh.isLeaf = true;
            bvh.hitable = bvh.geos[0];
            stackIndex -= 1;
            continue;
        }
        var parentGeoNum: i32 = bvh.geoNum;

        sortedObjs = sort_bvh_array(bvh.geos, bvh.geoNum, axis_x);
        //var sortedObjs: array<Hitable, GEO_NUM> = bvh.geos;
        var mid: i32 = parentGeoNum / 2;


        var left: BVH;
        left.geos = array_slice(sortedObjs, 0, mid);
        left.geoNum = max(mid, 1);
        left.isLeaf =false;

        var right: BVH;
        right.geos = array_slice(sortedObjs, mid, bvh.geoNum);
        right.isLeaf = false;
        right.geoNum = max(1, parentGeoNum - mid);

        // left : 0 - mid
        // right: mid - geoNum-1

        bvh_dict_arr[currentBVHDictIndex] = left;
        bvh.left = currentBVHDictIndex;

        currentBVHDictIndex += 1;
        bvh_dict_arr[currentBVHDictIndex] = right;
        bvh.right = currentBVHDictIndex;

        stack[stackIndex] = bvh.left;
        stackIndex += 1;
        stack[stackIndex] = bvh.right;
    }

    var container: BVHContainer;
    container.root = rootBVH;
    container.dict = bvh_dict_arr;
    return container;
}
*/