#include "./Collider.hpp"

bool Collider::checkCollisionAABB(const AABB &a, AABB &b)
{
    return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
           (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
           (a.min.z <= b.max.z && a.max.z >= b.min.z);
}

bool Collider::checkCollisionSphere(const sphere& a, const sphere& b) {
    float dist = glm::length(a.center - b.center);
    return dist < (a.radius + b.radius);
}