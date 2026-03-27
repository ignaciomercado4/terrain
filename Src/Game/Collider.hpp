#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>

struct AABB
{
    glm::vec3 min, max;
};

struct sphere {
    glm::vec3 center;
    float radius;
};

class Collider
{
private:
    
public:
    static bool checkCollisionAABB(const AABB& a, AABB& b);
    static bool checkCollisionSphere(const sphere& a, const sphere& b);
};

#endif