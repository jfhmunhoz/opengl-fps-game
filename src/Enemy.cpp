#include "Enemy.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <algorithm>

Enemy::Enemy(glm::vec3 position, glm::vec3 targetPosition, float speed)
    : position(position), targetPosition(targetPosition), alive(true), speed(speed)
{
}

glm::vec3 Enemy::getPosition() const
{
    return position;
}

glm::vec3 Enemy::getNextPosition(float deltaTime, glm::vec3 targetPosition)
{
    direction = glm::vec3((targetPosition.x - position.x), 0.0f, (targetPosition.z - position.z));
    direction = glm::normalize(direction);
    glm::vec3 displacement = glm::vec3(0.0f, 0.0f, 0.0f);

    displacement = speed * deltaTime *  direction;
    
    return glm::vec3(position.x+displacement.x, 0.0f, position.z+displacement.z);
}

float Enemy::getAngle() const
{
    return -std::atan2(-direction.x, direction.z);
}

void Enemy::update(float deltaTime, glm::vec3 targetPosition)
{
    if(!collision)
    {
        glm::vec3 nextPos = getNextPosition(deltaTime, targetPosition);
        position.x = nextPos.x;
        position.y = nextPos.y;
        position.z = nextPos.z;
    }

    direction = glm::vec3((targetPosition.x - position.x), 0.0f, (targetPosition.z - position.z));
}



glm::vec3 Enemy::getTargetPosition() const
{
    return targetPosition;
}

glm::vec3 Enemy::getBoundingBox() const
{
    return glm::vec3(0.5f, 1.0f, 0.5f);
}

bool Enemy::isAlive() const
{
    return alive;
}

void Enemy::die()
{
    alive = false;
}
