#pragma once

#define RAYX_CORE_INCLUDE

// RayXCore Essentials

#include "Ray.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Vec3.hpp"
#include "World.hpp"
#include "Hitable.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "PathTracer.hpp"
#include "AABB.hpp"

// RayXCore Hitables [Optional] [you can include individually also]

#ifndef RAYX_CORE_EXCLUDE_HITABLES

#include "Hitables/Sphere.hpp"
#include "Hitables/Plane.hpp"

#endif // RAYX_CORE_EXCLUDE_HITABLES

// RayXCore Materials [Optional] [you can include individually also]

#ifndef RAYX_CORE_EXCLUDE_MATERIALS

#include "Materials/Lambertian.hpp"
#include "Materials/Dielectric.hpp"
#include "Materials/Metal.hpp"

#endif // RAYX_CORE_EXCLUDE_MATERIALS

// RayXCore Textures [Optional] [you can include individually also]

#ifndef RAYX_CORE_EXCLUDE_TEXTURES

#include "Textures/SolidColor.hpp"
#include "Textures/CheckerTexture.hpp"

#endif // RAYX_CORE_EXCLUDE_TEXTURES