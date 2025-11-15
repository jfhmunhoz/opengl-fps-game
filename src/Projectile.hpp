#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <glm/vec3.hpp>

class Projectile {
public:
    Projectile(glm::vec3 position, glm::vec3 direction);
    void update(float deltaTime);
    void render();
    glm::vec3 getPosition() const;
    bool isActive() const;
    
private:
    glm::vec3 position;
    glm::vec3 direction;
    float speed;
    float lifetime;
};

#endif
