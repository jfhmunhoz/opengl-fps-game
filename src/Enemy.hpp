#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Enemy {
public:
    Enemy(glm::vec3 position, glm::vec3 targetPosition, float speed);

    glm::vec3 getPosition() const;
    glm::vec3 getTargetPosition() const;
    float getAngle() const;
    glm::vec3 getBoundingBox() const;
    glm::vec3 getNextPosition(float deltaTime, glm::vec3 targetPosition);

    void update(float deltaTime, glm::vec3 targetPosition);

    void setColision(bool collided);

    bool isAlive() const;
    void die();
    
private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 targetPosition;
    bool alive;
    float speed;
    bool collision = false;
};

#endif
