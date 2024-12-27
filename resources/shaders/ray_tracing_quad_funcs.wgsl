fn quad_hit_ray_out_hit_record(quad: Quad, ray: Ray, tmin: f32, tmax: f32)-> HitRecord
{
    var hitRecord: HitRecord;
    var denom = dot(ray.dir, quad.normal);
    if (abs(denom) < 1e-8)
    {
        return hitRecord;
    }

    var t = (quad.D - dot(quad.normal, ray.orig)) / denom;
    if (t < tmin || t > tmax)
    {
        return hitRecord;
    }

    var intersection = ray_pos_at_t(ray, t);
    var planar_hitpt_vector: vec3f = intersection - quad.q;
    var alpha = dot(quad.w, cross(planar_hitpt_vector, quad.v));
    var beta = dot(quad.w, cross(quad.u, planar_hitpt_vector));

    if (!quad_hit_is_interior(alpha, beta))
    {
        return hitRecord;
    }

    hitRecord.uv = vec2f(alpha, beta);
    hitRecord.t = t;
    hitRecord.position = intersection;
    hitRecord.normal = quad.normal;
    hitRecord.isHit = true;
    return hitRecord;
}

fn quad_hit_is_interior(alpha: f32, beta: f32)-> bool
{
    if (alpha > 0 && alpha < 1 && beta > 0 && beta < 1)
    {
        return true;
    }
    return false;
}