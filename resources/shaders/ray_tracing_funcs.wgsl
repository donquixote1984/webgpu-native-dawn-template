fn linear_to_gamma(linear_color: f32)->f32
{
    if (linear_color > 0)
    {
        return sqrt(linear_color);
    }
    return 0.0f;
}

fn linear_to_gamma3(linear_color: vec3f)->vec3f
{
    return vec3f(linear_to_gamma(linear_color.x), linear_to_gamma(linear_color.y), linear_to_gamma(linear_color.z));
}
fn random21(co:vec2f) -> f32 {
    return fract(sin(dot(co, vec2f(12.9898, 78.233))) * 43758.5453);
}


fn random12(seed: f32)->vec2f
{
    var p3:vec3f = fract(vec3f(seed) * vec3(.1031, .1030, .0973));
	p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xx+p3.yz)*p3.zy);
}
fn random13(seed: f32)->vec3f
{
   var p3:vec3f = fract(vec3(seed) * vec3(.1031, .1030, .0973));
   p3 += dot(p3, p3.yzx+33.33);
   return fract((p3.xxy+p3.yzz)*p3.zyx); 
}

fn random23(p: vec2f)->vec3f
{
	var p3:vec3f = fract(vec3f(p.x, p.y, p.x) * vec3f(.1031, .1030, .0973));
    p3 += dot(p3, p3.yxz+33.33);
    return fract((p3.xxy+p3.yzz)*p3.zyx);
}

fn randomUnitSphere(seed: vec3f)->vec3f
{
    var r: vec3f = random23(seed.xy);
    var theta: f32 = 2.0 * PI * r.x;
    var phi: f32 = acos(r.y);

    var x = sin(phi) * cos(theta);
    var y = sin(phi) * sin(theta);
    var z = cos(phi);

    return vec3f(x, y, z);
}

fn randomHemiSphere(normal: vec3f, uv: vec2f)->vec3f
{
    var r: vec3f = random23(uv);
    var u1:f32 = r.x;
    var u2:f32 = r.y;
    var theta: f32 = 2.0 * PI * u1;
    var phi: f32 = acos(u2);

    var x = sin(phi) * cos(theta);
    var y = sin(phi) * sin(theta);
    var z = cos(phi);

    var tangent: vec3f = normalize(cross(normal, vec3f(0.0, 0.0, 1.0)));
    if (length(tangent) < 0.001) {
        tangent = normalize(cross(normal, vec3f(1.0, 0.0, 0.0)));
    }
    var bitangent:vec3f = cross(normal, tangent);

    // Transform the random vector to the correct orientation
    var randomVec: vec3f = x * tangent + y * bitangent + z * normal;

    return normalize(randomVec);
}
fn length2v3(v: vec3f ) -> f32
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

fn randomHemiSphere2(normal: vec3f, uv: vec2f) ->vec3f
{
    var max_iter: i32 = 20;
    var index: i32 = 0;
    var result: vec3f = normalize(random23(uv) * 2.0f - 1.0f);
    while(true)
    {
        if(index > max_iter)
        {
            break;
        }
        var kun: vec3f = random23(uv + random12(f32(index))) * 2.0f - 1.0f;
        if (length2v3(kun) > 0.01f &&length2v3(kun) < 1.0f)
        {
            if (dot(kun, normal) > 0.0f)
            {
                result = normalize(kun);
            }
            else
            {
                result = -normalize(kun);
            }
            break;
        }
        index+=1;
    }
    return result;
}

fn ray_pos_at_t(ray: Ray, t: f32)->vec3f
{
    return ray.orig + t * ray.dir;
}
fn create_empty_hit_record()->HitRecord
{
    var hr: HitRecord;
    hr.isHit = false;
    return hr;
}


fn hitable_hit_ray_out_hit_record(hitable: Hitable, r: Ray, tmin: f32, tmax: f32) -> HitRecord
{
    var hitRecord: HitRecord;
    if (hitable._type == PRIM_TYPE_SPHERE)
    {
        hitRecord = sphere_hit_ray_out_hit_record(get_sphere_from_hittable_ray(hitable, r), r, tmin, tmax);
    }

    if (hitable._type == PRIM_TYPE_QUAD)
    {
        hitRecord = quad_hit_ray_out_hit_record(get_quad_from_hitable(hitable), r, tmin, tmax);
    }
   
    hitRecord.material = hitable.material;
    return hitRecord;
}


fn write_color(ray: Ray)->vec3f
{
    var a = 0.5 * (ray.dir.y + 1.0);
    return vec3f((1.0-a) * vec3f(1.0, 1.0, 1.0)+ a * vec3f(0.5f, 0.7f, 1.0f));
}
fn light_color(ray: Ray)->vec3f
{
    var a = 0.5 * (ray.dir.y + 1.0);
    return DEFAULT_BACKGROUND;
    //return vec3f((1.0-a) * vec3f(1.0, 1.0, 1.0)+ a * vec3f(0.5f, 0.7f, 1.0f));
}

fn bvh_ray_hit(r: Ray, tmin: f32, tmax:f32) -> HitRecord
{
    var stackIndex = 0;
    var stack: array<i32, 20>;
    var hitRecord: HitRecord;
    var closest_so_far = tmax;
    while(stackIndex >= 0)
    {
        var currentBVHIndex = stack[stackIndex];
        stackIndex -= 1;
        var node: BVHNode = world.bvhList[currentBVHIndex];
        if (node.isLeaf > 0)
        {
            var hitable: Hitable = uHitableList.hitableList[node.hitable];
            /*check hitable aabb*/
            //hitRecord =hitable_hit_ray_out_hit_record(hitable, r, 0, 1000);
                
            var newHitRecord = hitable_hit_ray_out_hit_record(hitable, r, tmin, closest_so_far);

            if (newHitRecord.isHit) {
                if (!hitRecord.isHit) {
                    hitRecord = newHitRecord;
                    closest_so_far = hitRecord.t;
                } else {
                    if (newHitRecord.t < closest_so_far) {
                        hitRecord = newHitRecord;
                        closest_so_far = hitRecord.t;
                    }
                }
            }

            //return hitRecord;
            continue; 
        }

        if (node.left > 0) {
            var left: BVHNode = world.bvhList[node.left];
            if (check_ray_hit_on_aabb_tmin_tmax(r, left.aabb, tmin, tmax)) {
                stackIndex += 1;
                stack[stackIndex] = node.left;
            }
        }
        
        if (node.right > 0) {
            var right: BVHNode = world.bvhList[node.right];
            if (check_ray_hit_on_aabb_tmin_tmax(r, right.aabb, tmin, tmax)) {
                stackIndex += 1;
                stack[stackIndex] = node.right;
            }
        }
    }

    return hitRecord;
}
#include "ray_tracing_box_funcs.wgsl"
#include "ray_tracing_sphere_funcs.wgsl"
#include "ray_tracing_quad_funcs.wgsl"

fn bvh_hit_ray_out_hit_record(r:Ray, tmin: f32, tmax: f32) -> HitRecord
{
    var closest_so_far = tmax;
    var hit_anything: bool = false;
    var result: HitRecord;
    /*
    for (var i: i32 = 0; i < GEO_NUM; i++)
    {
        var hitable = hitables[i];
        
        var hitRecord: HitRecord = hitable_hit_ray_out_hit_record(hitable, r, tmin, closest_so_far);
        if (hitRecord.isHit)
        {
            result = hitRecord;
            closest_so_far = hitRecord.t;
        }
    }
    */
    //var testaabb: AABB;
    //testaabb.min = vec4f(-0.2, -0.2, -0.2, 1.0);
    //testaabb.max = vec4f(0.2, 0.2, 0.2, 1.0f);
    if (!check_ray_hit_on_aabb(r, world.root.aabb)) {
    //if (!check_ray_hit_on_aabb(r, testaabb)) {
        result.isHit = false;
        return result;
    } else {
        result = bvh_ray_hit(r, tmin, tmax);
        //result.isHit = true;
    }
    return result;
}
fn hitable_list_hit_ray_out_hit_record(hitables: array<Hitable, GEO_NUM>, r:Ray, tmin: f32, tmax: f32) -> HitRecord
{
    var closest_so_far = tmax;
    var hit_anything: bool = false;
    var result: HitRecord;
    for (var i: i32 = 0; i < GEO_NUM; i++)
    {
        var hitable = hitables[i];
        
        var hitRecord: HitRecord = hitable_hit_ray_out_hit_record(hitable, r, tmin, closest_so_far);
        if (hitRecord.isHit)
        {
            result = hitRecord;
            closest_so_far = hitRecord.t;
        }
    }

    return result;
}

fn hit_scatter_on_material(ray: Ray, hitRecord: HitRecord, seed: vec3f)-> ScatterResult
{
    var scatterResult: ScatterResult;
    scatterResult.absorbed = false;
    var result: Ray = ray;
    result.orig = hitRecord.position + hitRecord.normal * 0.01;
    var material: HitableMaterial = hitRecord.material;
    if (material._type == MAT_METAL)
    {
        result.dir = reflect(ray.dir, hitRecord.normal);
    }
    else if (material._type == MAT_LAM || material._type == MAT_TEXTURE)
    {
       //result.dir = normalize(randomUnitSphere(seed) + hitRecord.normal); //randomHemiSphere(hitRecord.normal, seed) + hitRecord.normal;
        result.dir = randomHemiSphere(hitRecord.normal, seed.xy); //  + hitRecord.normal;
        if (length(result.dir)<1e-3)
        {
            result.dir = hitRecord.normal;
        }
    }
    else if (material._type == MAT_DIEL)
    {
        var ri: f32;
        if (hitRecord.frontFace)
        {
            ri = 1.0f / material.refractIndex;
        } else {
            ri = material.refractIndex;
        }
        var unit_dir = normalize(ray.dir);
        var cos_theta: f32 = min(dot(-unit_dir, hitRecord.normal), 1.0f);
        var sin_theta: f32 = sqrt(1.0f - cos_theta * cos_theta);
        var cannot_refract = ri * sin_theta > 1.0f;
        if (cannot_refract || reflectance(cos_theta, ri) > random21(seed.xy))
        {
            result.dir = reflect(unit_dir, hitRecord.normal);
        } else {
            result.dir = refract(unit_dir, hitRecord.normal, ri);
        }
    }
    else if(material._type == MAT_CHECKER)
    {
        result.dir = randomUnitSphere(seed) + hitRecord.normal;
        if (length(result.dir)<1e-3)
        {
            result.dir = hitRecord.normal;
        }
    } else if (material._type == MAT_EMISSIVE)
    {
        scatterResult.absorbed = true;
    }


    scatterResult.ray = result;
    return scatterResult;
}

#include "ray_tracing_material_color.wgsl"

fn reflectance(cosine: f32, refraction_index: f32) -> f32
{
        // Use Schlick's approximation for reflectance.
        var r0 = (1.0f - refraction_index) / (1.0f + refraction_index);
        r0 = r0*r0;
        return r0 + (1.0f-r0)*pow((1 - cosine),5);
}

fn ray_color_bvh(r: Ray, uvw: vec3f) ->vec3f
{
    var i: i32 = 0;
    var currentRay: Ray = r;
    var color: vec3f = vec3f(1.0f, 1.0f, 1.0f);
    var factor: f32 = 1.0f;

    while(true)
    {
        if (i > MAX_BOUNCE)
        {
            // get light color;
            //color *= light_color(currentRay) * factor;
            color = vec3f(0.0f, 0.0f, 0.0f);
            break;
        }
        var hitRecord: HitRecord = bvh_hit_ray_out_hit_record(currentRay, 0.001, 1000);

        if (hitRecord.isHit)
        {
            //var bounceDir = randomHemiSphere(hitRecord.normal, uv + random12(f32(i)));
            var scatterResult = hit_scatter_on_material(currentRay, hitRecord, uvw + random13(f32(i)));
            if (scatterResult.absorbed) {
                var emissive_color = hit_color_on_material(currentRay, hitRecord);
                //return vec3f(1.0, 0.0, 0.0);
                color = color * (emissive_color);
                break;
            }
            currentRay = scatterResult.ray;
            color *= hit_color_on_material(currentRay, hitRecord);
            
            //factor *= ATTENUATION;
        }
        else
        {
            // get light color;
            color *= light_color(currentRay) * factor;
            break;
        }
        i+=1;
    }

    return linear_to_gamma3(color);
}


/*

fn ray_color(world1: array<Hitable, GEO_NUM>, r: Ray, uvw: vec3f) -> vec3f
{
    var i: i32 = 0;
    var currentRay: Ray = r;
    var color: vec3f = vec3f(1.0f, 1.0f, 1.0f);
    var factor: f32 = 1.0f;
    while(true)
    {
        if (i > MAX_BOUNCE)
        {
            // get light color;
            color *= light_color(currentRay) * factor;
            break;
        }
        var hitRecord: HitRecord = hitable_list_hit_ray_out_hit_record(world1, currentRay, 0.001, 1000);

        if (hitRecord.isHit)
        {
            //var bounceDir = randomHemiSphere(hitRecord.normal, uv + random12(f32(i)));
            currentRay = hit_scatter_on_material(currentRay, hitRecord, uvw + random13(f32(i)));
            color *= hit_color_on_material(currentRay, hitRecord);
            //factor *= ATTENUATION;
        }
        else
        {
            // get light color;
            color *= light_color(currentRay) * factor;
            break;
        }
        i+=1;
    }

    return linear_to_gamma3(color);
} 
*/