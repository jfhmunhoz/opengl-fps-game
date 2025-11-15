#include "Enemy.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <algorithm>

Enemy::Enemy(glm::vec3 position, glm::vec3 targetPosition)
    : position(position), targetPosition(targetPosition), health(100.0f), speed(2.0f)
{
}

void Enemy::update(float deltaTime)
{
    if (!isAlive()) return;
    
    glm::vec3 direction = glm::normalize(targetPosition - position);
    position += direction * speed * deltaTime;
    
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
}

void Enemy::render()
{
    // TODO: Implement rendering using g_VirtualScene
}

glm::vec3 Enemy::getPosition() const
{
    return position;
}

glm::vec3 Enemy::getBoundingBox() const
{
    return glm::vec3(0.5f, 1.0f, 0.5f);
}

bool Enemy::isAlive() const
{
    return health > 0.0f;
}

void Enemy::takeDamage(float damage)
{
    health = std::max(0.0f, health - damage);
}
