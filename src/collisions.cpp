#include "collisions.hpp"
#include <glm/geometric.hpp>
#include <cmath>

bool CollisionManager::sphereSphereCollision(glm::vec3 pos1, float radius1,
                                              glm::vec3 pos2, float radius2)
{
    float distance = glm::length(pos2 - pos1);
    return distance < (radius1 + radius2);
}

bool CollisionManager::rayToSphere(glm::vec3 rayOrigin, glm::vec3 rayDir,
                                    glm::vec3 spherePos, float radius)
{
    glm::vec3 oc = rayOrigin - spherePos;
    float a = glm::dot(rayDir, rayDir);
    float b = 2.0f * glm::dot(oc, rayDir);
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0f * a * c;
    
    return discriminant >= 0.0f;
}

bool CollisionManager::spherePlaneCollision(
    glm::vec3 sphereCenter,
    float radius,
    glm::vec3 planePoint,
    glm::vec3 planeNormal
)
{
    float dist = glm::dot(sphereCenter - planePoint, planeNormal);
    //return fabs(dist) <= radius;
    return dist <= radius && dist >= 0.0f;
}
