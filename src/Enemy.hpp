#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Enemy {
public:
    Enemy(glm::vec3 position, glm::vec3 targetPosition);
    void update(float deltaTime);
    void render();
    glm::vec3 getPosition() const;
    glm::vec3 getBoundingBox() const;
    bool isAlive() const;
    void takeDamage(float damage);
    
private:
    glm::vec3 position;
    glm::vec3 targetPosition;
    float health;
    float speed;
    glm::mat4 modelMatrix;
};

#endif
