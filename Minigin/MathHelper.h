#pragma once
#include <corecrt_math.h>

template<typename t>
static t Magnitude(const glm::vec3& vector)
{
	return static_cast<t>(sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

template<typename t>
static t ToDegrees(const t& angle)
{
	return static_cast<t >(angle * 180.f / M_PI);
}
template<typename t>
static t ToRadians(const t& angle)
{
	return static_cast<t>(angle * M_PI / 180.f);
}

class MathHelper final
{
public:
	static void InverseX(glm::vec2& vector) { vector.x = -vector.x;}
	static void InverseX(glm::vec3& vector) { vector.x = -vector.x;}
	static void InverseX(glm::vec4& vector) { vector.x = -vector.x;}
				
	static void InverseY(glm::vec2& vector) { vector.y = -vector.y;}
	static void InverseY(glm::vec3& vector) { vector.y = -vector.y;}
	static void InverseY(glm::vec4& vector) { vector.y = -vector.y;}
				
	static void InverseZ(glm::vec3& vector) { vector.z = -vector.z;}
	static void InverseZ(glm::vec4& vector) { vector.z = -vector.z;}
				
	static void InverseW(glm::vec4& vector) { vector.w = -vector.w;}

};