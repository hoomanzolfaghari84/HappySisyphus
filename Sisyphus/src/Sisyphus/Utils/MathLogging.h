#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp> // for glm::row()

// Helper for vec3
inline void LogVec3(const glm::vec3& v, const std::string& name)
{
    std::cout << name << ": ("
        << v.x << ", " << v.y << ", " << v.z << ")\n";
}

// Helper for mat4
inline void LogMat4(const glm::mat4& m, const std::string& name)
{
    std::cout << name << ":\n";
    for (int i = 0; i < 4; i++)
    {
        const glm::vec4 row = glm::row(m, i);
        std::cout << "  ["
            << row.x << ", " << row.y << ", "
            << row.z << ", " << row.w << "]\n";
    }
}