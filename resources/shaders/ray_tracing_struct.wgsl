const MAT_LAM:     i32 = 101;
const MAT_METAL:   i32 = 202;
const MAT_DIEL:    i32 = 303;
const MAT_CHECKER: i32 = 404;
const MAT_TEXTURE: i32 = 505;
const MAT_EMISSIVE: i32 = 606;

const PRIM_TYPE_SPHERE = 0;
const PRIM_TYPE_CUBE = 1;
const PRIM_TYPE_QUAD = 2;
const PRIM_TYPE_BOX = 3;
const MAX_INF = 1e10;
const AXIS_X = 0;
const AXIS_Y = 1;
const AXIS_Z = 2;
const MAX_BVH_DICT_SIZE = 200;
const MAX_HITABLE_SIZE = 64;
const PI = 3.1415926536;

const DEFAULT_BACKGROUND = vec3f(0.0f, 0.0f, 0.0f);

struct PrimitiveType
{
    _type: i32,
}

struct AABB
{
    min: vec4f,
    max: vec4f,
}



struct Ray
{
    orig: vec3f,
    dir: vec3f,
    time: f32,
};

struct ScatterResult
{
    ray: Ray,
    absorbed: bool,
};

struct Properties
{
    isMB: bool,
    mbTowards: vec3f,
    center: vec3f,
    radius: f32,
    material: Material,
}

struct Material
{
    color: vec3f,
    category: i32,
    refractIndex: f32,
};

struct Sphere
{
    center: vec3f,
    radius: f32,
}

struct Box
{
    min: vec4f,
    max: vec4f,
}

struct Quad
{
    q: vec3f,
    u: vec3f,
    v: vec3f,
    w: vec3f,
    D: f32,
    normal: vec3f,
}

struct HitableMaterial
{
    _type: i32,
    refractIndex: f32,
    factor: f32,
    color: vec4f,
}

struct HitableProperties
{
    dim: vec4f,
    mbTowards: vec4f,
    center: vec4f,
    min: vec4f,
    max: vec4f,
    normal: vec4f,
    u: vec4f,
    v: vec4f,
    extra: vec4f,
}


struct Hitable
{
    _type: i32,
    index: i32,
    material: HitableMaterial,
    properties: HitableProperties,
    aabb: AABB,
}

struct HitableList
{
    count: i32,
    hitableList: array<Hitable, MAX_HITABLE_SIZE>,
}

struct HitRecord
{
    position: vec3f,
    normal: vec3f,
    t: f32,
    isHit: bool,
    frontFace: bool,
    material: HitableMaterial,
    uv: vec2f,
};

struct Screen
{
    width: i32,
    height: i32,
    aspectRatio:f32,
};

struct BVHNode
{
    left: i32,
    right: i32,
    isLeaf: i32,
    hitable: i32,
    aabb: AABB,
}

struct BVH
{
    root: BVHNode,
    bvhList: array<BVHNode, MAX_BVH_DICT_SIZE>,
}


fn get_sphere_from_hittable(hitable: Hitable)->Sphere
{
    var sphere: Sphere;

    sphere.radius = hitable.properties.dim.x;
    sphere.center = hitable.properties.center.xyz;
    return sphere;
}

fn get_quad_from_hitable(hitable: Hitable)->Quad
{
    var quad: Quad;
    quad.q = hitable.properties.center.xyz;
    quad.w= hitable.properties.extra.xyz;
    quad.D = hitable.properties.extra.w;
    quad.u = hitable.properties.u.xyz;
    quad.v = hitable.properties.v.xyz;
    quad.normal = hitable.properties.normal.xyz;
    return quad;
}

fn get_sphere_from_hittable_ray(hitable: Hitable, r: Ray)->Sphere
{
    var sphere: Sphere;
    sphere.radius = hitable.properties.dim.x;
    sphere.center = hitable.properties.center.xyz;
    if (hitable.properties.dim.y >.0f)
    {
        var tmpR = Ray(hitable.properties.center.xyz, hitable.properties.mbTowards.xyz, 0.0f);
        sphere.center = ray_pos_at_t(tmpR, r.time);
    }
    
    return sphere;
}