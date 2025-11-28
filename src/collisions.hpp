#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include <glm/vec3.hpp>

class CollisionManager {
public:
    static bool sphereSphereCollision(glm::vec3 pos1, float radius1,
                                      glm::vec3 pos2, float radius2);
    static bool rayToSphere(glm::vec3 rayOrigin, glm::vec3 rayDir,
                           glm::vec3 spherePos, float radius);
    bool spherePlaneCollision(glm::vec3 sphereCenter, float radius, glm::vec3 planePoint, glm::vec3 planeNormal);
};

#endif
