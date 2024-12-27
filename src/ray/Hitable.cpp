#include "Hitable.h"
#include "../uniforms/RayHitableUniform.h"

HitableUniform Hitable::ToHitableUniform()
{
    HitableUniform uniform;


    uniform._type = static_cast<int>(this->type);
    uniform.aabb = this->aabb;
    uniform.aabb.PadToMinimum();
    uniform.index = index;
    uniform.material = material.ToHitableMaterialUniform();
    uniform.properties = properties.ToHitablePropertiesUniform();

    return uniform;
}

HitablePropertiesUniform HitableProperties::ToHitablePropertiesUniform()
{
    HitablePropertiesUniform uniform;
    uniform.dim = glm::vec4(radius, 0.0f, 0.0f, 0.0f);
    uniform.center = center;
    uniform.min = min;
    uniform.max = max;
    uniform.mbTowards = mbTowards;
    uniform.u = u;
    uniform.v = v;
    uniform.normal = normal;
    uniform.extra = extra;
    return uniform;
}

HitableMaterialUniform HitableMaterial::ToHitableMaterialUniform()
{
    HitableMaterialUniform uniform;
    uniform.color = color;
    uniform.refractIndex = refractIndex;
    uniform._type = static_cast<int>(type);
    uniform.factor = factor;
    return uniform;
}

int Hitable::_index= 0;